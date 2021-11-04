
#include "philosophers.h"

BOOL	start_simulation(t_env *env)
{
	int		i;

	env->philos = (t_philo *)malloc(
		env->philo_count * sizeof(t_philo));
	if (env->philos == NULL)
		return (1);
	env->forks = (pthread_mutex_t *)malloc(
		env->philo_count * sizeof(pthread_mutex_t));
	if (env->forks == NULL)
		return (1);
	pthread_mutex_init(&env->logger, NULL);
	i = -1;
	while (++i < env->philo_count)
		pthread_mutex_init(&env->forks[i], NULL);
	env->start_time = time_now();
	i = -1;
	while (++i < env->philo_count)
	{	
		env->philos[i].id = i;
		env->philos[i].status = 0;
		env->philos[i].eat_count = 0;
		env->philos[i].last_meal_time = env->start_time;
		env->philos[i].env = env;
		// pthread_mutex_init(&env->philos[i].eat_mutex, NULL);
	}
	return (create_threads(env));
}

void	supervise(t_env *env)
{
	int		i;
	int		flag;

	while (1)
	{
		i = -1;
		flag = env->max_meals;
		while (++i < env->philo_count)
		{
			flag &= env->philos[i].eat_count;
			if (env->philos[i].eat_count == env->max_meals)
				continue ;
			if (env->philos[i].status != EATING 
				&& (time_now() - env->philos->last_meal_time >= env->time_to_die))
				return died(&env->philos[i]);
		}
		if (flag == env->max_meals)
			break ;
	}
	
}

BOOL	create_threads(t_env *env)
{
	int			i;
	pthread_t	threads[env->philo_count];

	i = -1;
	while (++i < env->philo_count)
	{

		if (pthread_create(&threads[i], NULL, philo_routine, &env->philos[i]))
			return (print_error(ERR_THRD_CREATE));
		usleep(60);
	}
	supervise(env);
	return (0);
}

void	*philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	while (ph->env->max_meals == -1 || ph->eat_count < ph->env->max_meals)
	{
		thinking(ph);
		take_forks(ph);
		eating(ph);
		put_forks(ph);
		sleeping(ph);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	if (argc < 5)
	{
		printf("Error\n%s\n", ERR_FEW_ARGS);
		return (EXIT_FAILURE);
	}
	else if (argc > 6)
		return (print_error(ERR_MANY_ARGS));
	if (parse_args(env, argc, argv))
		return (print_error(ERR_INV_ARGS));
	env->dead = 0;
	if (start_simulation(env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
