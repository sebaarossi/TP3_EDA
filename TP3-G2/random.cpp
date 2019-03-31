#include <cstdlib>



double RandomValue(double min, double max)
{
	return (min + ((double)rand() / RAND_MAX) * (max - min));
}

int RandomSign(void)
{
	return (RandomValue(-1, 1) > 0 ? 1 : -1);
}