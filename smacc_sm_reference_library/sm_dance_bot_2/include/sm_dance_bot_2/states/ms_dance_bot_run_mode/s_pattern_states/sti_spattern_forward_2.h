namespace sm_dance_bot_2
{
namespace s_pattern_states
{
// STATE DECLARATION
struct StiSPatternForward2 : public smacc::SmaccState<StiSPatternForward2, SS>
{
  using SmaccState::SmaccState;

// TRANSITION TABLE
  typedef mpl::list<
  
  Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StiSPatternRotate3>,
  Transition<EvActionAborted<ClMoveBaseZ, OrNavigation>, StiSPatternRotate2>
  
  >reactions;

// STATE FUNCTIONS
  static void staticConfigure()
  {
  }

  void runtimeConfigure()
  {
    auto &superstate = this->context<SS>();

    this->configure<OrNavigation, CbNavigateForward>(SS::pitch2_lenght_meters());
    this->configure<OrLED, CbLEDOn>();
  }
};
} // namespace s_pattern_states
} // namespace sm_dance_bot_2