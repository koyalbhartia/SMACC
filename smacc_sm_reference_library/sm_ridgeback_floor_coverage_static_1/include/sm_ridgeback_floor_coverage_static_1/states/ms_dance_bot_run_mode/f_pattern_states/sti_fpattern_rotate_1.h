namespace sm_ridgeback_floor_coverage_static_1
{
  namespace f_pattern_states
  {
    // STATE DECLARATION
    template <typename SS>
    struct StiFPatternRotate1 : smacc::SmaccState<StiFPatternRotate1<SS>, SS>
    {
      typedef SmaccState<StiFPatternRotate1<SS>, SS> TSti;
      using TSti::context_type;
      using TSti::SmaccState;

      // TRANSITION TABLE
      typedef mpl::list<

          Transition<EvCbSuccess<CbAbsoluteRotate, OrNavigation>, StiFPatternForward1<SS>>

          >
          reactions;

      // STATE FUNCTIONS
      static void staticConfigure()
      {
        float angle = 0;
        double offset = 7; // for a better behaving

        if (SS::direction() == TDirection::LEFT)
          angle = 90 + offset;
        else
          angle = -90 - offset;

        //TSti::template configure_orthogonal<OrNavigation, CbRotate>(angle);
        TSti::template configure_orthogonal<OrNavigation, CbAbsoluteRotate>(angle); // absolute aligned to the y-axis
        TSti::template configure_orthogonal<OrLED, CbLEDOff>();
      }

      void runtimeConfigure()
      {
      }
    };
  } // namespace f_pattern_states
} // namespace sm_ridgeback_floor_coverage_static_1