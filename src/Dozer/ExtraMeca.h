struct Sideway
{
  void left (int speed)
  {
    mecanum.motors[Left][Top].backward(speed);
    mecanum.motors[Left][Bottom].forward(speed);
    mecanum.motors[Right][Top].backward(speed);
    mecanum.motors[Right][Bottom].forward(speed);
  }
  void right (int speed)
  {
    mecanum.motors[Left][Top].forward(speed);
    mecanum.motors[Left][Bottom].backward(speed);
    mecanum.motors[Right][Top].forward(speed);
    mecanum.motors[Right][Bottom].backward(speed);
  }
};
struct Diagonal
{
  void forward (int speed)
  {
    mecanum.motors[Left][Top].forward(speed);
    mecanum.motors[Left][Bottom].stop();
    mecanum.motors[Right][Top].stop();
    mecanum.motors[Right][Bottom].forward(speed);
  }
  void backward (int speed)
  {
    mecanum.motors[Left][Top].stop();
    mecanum.motors[Left][Bottom].forward(speed);
    mecanum.motors[Right][Top].forward(speed);
    mecanum.motors[Right][Bottom].stop();
  }
};
class Mecaside
{
  public:
    Mecaside(int iSide)
    {
      side = iSide;
    }
    int side = 0;
    void forward(int speed)
    {
      mecanum.motors[side][0].forward(speed);
      mecanum.motors[side][1].forward(speed);
    }
    void backward(int speed)
    {
      mecanum.motors[side][0].backward(speed);
      mecanum.motors[side][1].backward(speed);
    }
    void stop()
    {
      mecanum.motors[side][0].stop();
      mecanum.motors[side][1].stop();
    }
};
