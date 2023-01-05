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
    void drift ()
    {
      mecanum.forward(1023);
      delay(700);
      left.forward(128);
      delay(300);
      sideway.right(1023);
      delay(500);
      right.forward(1023);
      left.forward(128);
      delay(100);
      left.forward(1023);
      right.forward(128);
      delay(100);
      mecanum.forward(1023);
      delay(500);
      mecanum.stop();
    }
};
