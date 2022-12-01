class AutoPilot
{
    public:
        AutoPilot() {}
        void findTheLineToTheLeft ()
        {
          sideway.left(512);
          while (blackLine.getPattern() != Position.Pattern.OnTheLine);
          mecanum.stop();
        }
        void findTheLineToTheRight ()
        {
          sideway.right(512);
          while (blackLine.getPattern() != Position.Pattern.OnTheLine);
          mecanum.stop();
        }
        void goBackToCherry ()
        {
          mecanum.backward(512);
          while (blackLine.getPattern() == Position.Pattern.OnTheLine && backDistance.getValue() != -1);
          if (blackLine.getPattern() != Position.Pattern.OnTheLine)
          {
            if (blackLine.getPattern() == Position.Pattern.OnTheRight)
            {
              left.backward(512);
              right.forward(512);
              while (blackLine.getPattern() != Position.Pattern.OnTheLine);
              mecanum.stop();
              goBackToCherry();
            }
          }
          else
          {
            mecanum.stop();
          }
        }
};
