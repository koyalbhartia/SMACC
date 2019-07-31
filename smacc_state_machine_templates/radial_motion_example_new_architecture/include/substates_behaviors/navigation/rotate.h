#pragma once

#include <smacc/smacc_state.h>
#include <boost/optional.hpp>

#include <tf/transform_listener.h>
#include <tf/tf.h>


class Rotate : public smacc::SmaccStateBehavior
{
 public:
  tf::TransformListener listener;

  smacc::SmaccMoveBaseActionClient *moveBaseClient_;

  smacc_planner_switcher::PlannerSwitcher* plannerSwitcher_;

  boost::optional<float> rotateDegree;

  Rotate()
  {

  }

  Rotate(float rotate_degree)
  {
    rotateDegree = rotate_degree;
  }

  virtual void onEntry() override
  {
    double  angle_increment_degree;

    if(!rotateDegree)
    {
        this->currentState->param("angle_increment_degree", angle_increment_degree, 90.0);
    }
    else
    {
       angle_increment_degree = *rotateDegree;
    }

    this->requiresComponent(moveBaseClient_ , ros::NodeHandle("move_base"));

    //this should work better with a coroutine and await
    ros::Rate rate(10.0);
    while (ros::ok())
    {
        tf::StampedTransform currentPose;
        try{
        listener.lookupTransform("/base_link", "/odom",  
                                ros::Time(0), currentPose);
        break;
        }
        catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
        }
    }   

    smacc::SmaccMoveBaseActionClient::Goal goal;
    goal.target_pose.header.frame_id = "/odom";
    goal.target_pose.header.stamp = ros::Time::now();

    auto currentAngle = tf::getYaw(goal.target_pose.pose.orientation);
    auto targetAngle = currentAngle + angle_increment_degree *M_PI/180.0;

    goal.target_pose.pose.orientation =tf::createQuaternionMsgFromYaw(targetAngle);

    moveBaseClient_->sendGoal(goal);
  }    
};
