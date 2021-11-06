
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
	ph->status = EATING;
	pthread_mutex_lock(&ph->eat_mutex);
	print_status(ph, TAKEN_FORK);
}

void	eating(t_philo *ph)
{
	print_status(ph, EATING);
	ph->last_meal_time = time_now();
	ph->eat_count++;
	usleep_wrapper(ph->env->time_to_eat);
	pthread_mutex_unlock(&ph->eat_mutex);
	ph->status = !EATING;
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
