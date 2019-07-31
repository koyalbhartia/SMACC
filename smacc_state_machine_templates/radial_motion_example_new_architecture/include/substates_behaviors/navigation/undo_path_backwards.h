#pragma once
#include <smacc/smacc_state.h>
#include <smacc_odom_tracker/odom_tracker.h>
#include <nav_msgs/Path.h>

class UndoPathBackwards : public smacc::SmaccStateBehavior
{
  tf::TransformListener listener;
    
  smacc::SmaccMoveBaseActionClient *moveBaseClient_;

  smacc_odom_tracker::OdomTracker* odomTracker_;

  smacc_planner_switcher::PlannerSwitcher* plannerSwitcher_;  

  virtual void onEntry() override
  {
    this->requiresComponent(moveBaseClient_ ,ros::NodeHandle("move_base"));
    this->requiresComponent(odomTracker_);
    this->requiresComponent(plannerSwitcher_ , ros::NodeHandle("move_base"));   

    nav_msgs::Path forwardpath = this->odomTracker_->getPath();
    this->odomTracker_->setWorkingMode(smacc_odom_tracker::WorkingMode::CLEAR_PATH_BACKWARD);
    
    smacc::SmaccMoveBaseActionClient::Goal goal;
    if ( forwardpath.poses.size()>0)
    {
      goal.target_pose = forwardpath.poses.front();
      this->plannerSwitcher_->setBackwardPlanner();
      moveBaseClient_->sendGoal(goal);
    }
  }    
};
