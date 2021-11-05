
#include "philosophers.h"

void	thinking(t_philo *ph)
{
	print_status(ph, THINKING);
}


void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->env->forks[ph->id]);
	print_status(ph, TAKEN_FORK);
	pthread_mutex_lock(&ph->env->forks[(ph->id + 1) % ph->env->philo_count]);
	print_status(ph, TAKEN_FORK);
}

# define RED                "\033[1;31m"
# define GREEN              "\033[1;32m"
# define WHITE              "\033[1;37m"
# define NO_COLOR           "\033[0m"

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->eat_mutex);
	put_str(GREEN);
	print_status(ph, EATING);
	put_str(NO_COLOR);
	ph->last_meal_time = time_now();
	ph->eat_count++;
	usleep_wrapper(ph->env->time_to_eat);
	pthread_mutex_unlock(&ph->eat_mutex);
}

void	put_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->env->forks[ph->id]);
	pthread_mutex_unlock(
		&ph->env->forks[(ph->id + 1) % ph->env->philo_count]);
}

void	died(t_philo *ph)
{
	ph->env->dead = 1;
	print_status(ph, DEAD);
}

void	sleeping(t_philo *ph)
{
	print_status(ph, SLEEPING);
	usleep_wrapper(ph->env->time_to_sleep);
}
