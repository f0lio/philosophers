
#include "philosophers.h"

unsigned	time_now()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1e3) + (curr_time.tv_usec / 1e3));
}

BOOL	parse_args(t_env *env, int argc, char **argv)
{
	env->philo_count = atoi(argv[1]);
	env->time_to_die = atoi(argv[2]);
	env->time_to_eat = atoi(argv[3]);
	env->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		env->max_meals = atoi(argv[5]);
	else
		env->max_meals = -1;
	// if invalid arg -> return 1
	return (0);
}

BOOL	init_env(t_env *env)
{
	int		i;

	env->philos = (t_philo *)malloc(env->philo_count * sizeof(t_philo));
	env->forks = (pthread_mutex_t *)malloc(env->philo_count * sizeof(pthread_mutex_t));
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
	create_threads(env);
	return (0);
}

// timestamp_in_ms X is thinking

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
		printf("%u %d died\n", time_now() - ph->env->start_time, ph->id + 1);
		return ;
	}
	printf("%u %d %s\n", time_now() - ph->env->start_time, ph->id + 1, msg);
	pthread_mutex_unlock(&ph->env->logger);
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
			// unsigned long x = time_now();
			if (env->philos[i].status != EATING 
				&& (time_now() - env->philos->last_meal_time > env->time_to_die))
			{
				// printf("%lu - %lu = %lu\n", env->philos->last_meal_time, x, x - env->philos-> last_meal_time);
				died(&env->philos[i]);
				return ;
			}
		}
		// printf("f[%d]\n", flag);
		if (flag == env->max_meals)
			break ;
		// usleep(20);
	}
	
}

void	create_threads(t_env *env)
{
	int			i;
	pthread_t	threads[env->philo_count];

	i = -1;
	while (++i < env->philo_count)
	{
		pthread_create(&threads[i], NULL, run_simulation, &env->philos[i]);
		//delay
		usleep(100);
	}
	supervise(env);
}

void	*run_simulation(void *philo)
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
	t_env	env;

	if (argc < 5)
	{
		printf("Error\n%s\n", ERR_FEW_ARGS);
		return (EXIT_FAILURE);
	}
	else if (argc > 6)
	{
		printf("Error\n%s\n", ERR_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	if (parse_args(&env, argc, argv))
		return (EXIT_FAILURE);
	if (init_env(&env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
