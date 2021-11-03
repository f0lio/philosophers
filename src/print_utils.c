
#include "philosophers.h"

size_t str_len(char *s)
{
	size_t l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

void	print_long(long l)
{
	long x;

	x = 0;
	if (l < 0)
	{
		put_char('-');
		x = -l;
	}
	else
		x = l;
	if (x < 10)
		put_char(x + 48);
	else
	{
		print_long(x / 10);
		put_char((x % 10) + 48);
	}
}

void	put_char(char c)
{
	write(1, &c, 1);
}

void	put_str(char *s)
{
	write(1, s, str_len(s));
}

BOOL	print_error(char *msg)
{
	put_str("Error\n");
	put_str(msg);
	put_str("\n");
	return (1);
}

void	print_status(t_philo *ph, BOOL status)
{
	char *msg;

	pthread_mutex_lock(&ph->env->logger);
	if (status == THINKING)
		msg = "is thinking";
	else if (status == TAKEN_FORK)
		msg = "has taken a fork";
	else if (status == EATING)
		msg = "is eating";
	else if (status == SLEEPING)
		msg = "is sleeping";
	else
	{
		printf("%u %d died\n", time_now() - ph->env->start_time, ph->id + 1); //?
		return ;
	}
	printf("%u %d %s\n", time_now() - ph->env->start_time, ph->id + 1, msg);
	pthread_mutex_unlock(&ph->env->logger);
}
