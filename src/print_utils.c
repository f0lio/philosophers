
#include "philosophers.h"

size_t str_len(char *s)
{
	size_t l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

void	put_str(int fd, char *s)
{
	write(fd, s, str_len(s));
}

BOOL	print_error(char *msg)
{
	put_str(STDERR_FILENO, "Error\n");
	put_str(STDERR_FILENO, msg);
	put_str(STDERR_FILENO, "\n");
	return (1);
}

void		clean_data(t_env *env)
{
	int i;

	i = 0;
	while (i < env->philo_count)
	{
		pthread_mutex_destroy(&env->forks[i]);
		pthread_mutex_destroy(&env->philos[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&env->logger);
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
		printf("%llu %d died\n", time_now() - ph->env->start_time, ph->id + 1);
		return ;
	}
	printf("%llu %d %s\n", time_now() - ph->env->start_time, ph->id + 1, msg); 
	pthread_mutex_unlock(&ph->env->logger);
}
