


class tweety
{
public:
  tweety();
  move(void);
  project(tweety * bird, int bird_count, double rand_jiggle_limit, double eyesight);
  move(double speed);

private:
  double speed;
  double x;
  double y;
  double angle;
  bool insight (const tweety& ,double bird);
  double new_x;
  double new_y;
  double new_angle;
  double eyesight;
  double random_jiggle;

}
