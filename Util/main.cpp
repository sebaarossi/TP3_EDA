int main (int arg c, char * argv[])
{

  tweety * birds = newtweety [bird_count];
  while (!quit)
  {
    for (int i=0; i < bird_count; i++)
    {
      b[i].project(b,bird_count,rand_jiggle_limit,eyesight);
    }
    for (int i=0; i < bird_count, i++)
    {
      b[i].move();
    }

    drawbirds();
    tickcount ++;
  }

  delete (birds);
}
