#include <stdio.h>

tweety :: project (tweety * birds, int bird_count,double rand_jiggle_limit, double eyesight)
{
  double angle_sum = 0;
  uint divider = 0;

  for(int i=0; i < bird_count, i++)
  {
    if(insight(birds[i],eyesight))
    {
      angle_sum += birds[i].angle;
      divider ++;
    }
  }

  new_angle = angle_sum/divider + getRandomJiggle(divider,rand_jiggle_limit)
}
