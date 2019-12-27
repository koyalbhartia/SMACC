#include <smacc/smacc.h>

namespace fpattern_substates
{

enum class TDirection
{
    LEFT,
    RIGHT
};

//HERE WE MAKE FORWARD DECLARATIONS OF ALL SUBSTATE ROUTINES
template <typename SS>
class SsrFPatternRotate1;

template <typename SS>
class SsrFPatternForward1;

template <typename SS>
class SsrFPatternReturn1;

template <typename SS>
class SsrFPatternRotate2;

template <typename SS>
class SsrFPatternForward2;

template <typename SS>
class SsrFPatternStartLoop;
} // namespace fpattern_substates

namespace sm_dance_bot
{
namespace SS4
{

using namespace fpattern_substates;

struct SsFPattern1 : smacc::SmaccState<SsFPattern1, MsDanceBotRunMode, SsrFPatternStartLoop<SsFPattern1>>
{
public:
    using SmaccState::SmaccState;

    typedef mpl::list<
        // Expected event
        smacc::transition<EvLoopEnd<SsrFPatternStartLoop<SsFPattern1>>, StNavigateForward2, ENDLOOP> //,

        // Error events
        //smacc::transition<smacc::EvTopicMessageTimeout<CbLidarSensor>, StAcquireSensors>,
        //smacc::transition<EvActionAborted<smacc::ClMoveBaseZ, OrNavigation>, StNavigateToWaypointsX>
        >
        reactions;

    // superstate parameters
    static constexpr float ray_lenght_meters() { return 2; }
    static constexpr float pitch_lenght_meters() { return 0.6; }
    static constexpr int total_iterations() { return 2; }
    static constexpr TDirection direction() { return TDirection::RIGHT; }

    // superstate state variables
    int iteration_count;

    static void onDefinition()
    {
        //static_configure<OrObstaclePerception, CbLidarSensor>();
    }

    void onInitialize()
    {
        iteration_count = 0;
    }
}; // namespace SS4

//forward declaration for the superstate

} // namespace SS4
} // namespace sm_dance_bot

#include <sm_dance_bot/states/f_pattern/ssr_fpattern_rotate_1.h>
#include <sm_dance_bot/states/f_pattern/ssr_fpattern_forward_1.h>
#include <sm_dance_bot/states/f_pattern/ssr_fpattern_return_1.h>
#include <sm_dance_bot/states/f_pattern/ssr_fpattern_rotate_2.h>
#include <sm_dance_bot/states/f_pattern/ssr_fpattern_forward_2.h>
#include <sm_dance_bot/states/f_pattern/ssr_fpattern_loop_start.h>
