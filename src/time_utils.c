
#include "philosophers.h"

unsigned long long time_now()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1e3) + (curr_time.tv_usec / 1e3));
}

void	usleep_wrapper(unsigned time)
{
	t_ul	start;

	start = time_now();
	while ((time_now() - time) < start)
		usleep(100);
}
