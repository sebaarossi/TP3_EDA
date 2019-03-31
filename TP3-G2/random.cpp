#include <cstdlib>



double RandomValue(double min, double max)
{
	return (min + ((double)rand() / RAND_MAX) * (max - min));
}