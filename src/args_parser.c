
#include "philosophers.h"

int	str_to_int(char *s)
{
	return (atoi(s)); //?????
}

int	check_and_parse(char *s)
{
	unsigned i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (str_to_int(s));
}

BOOL	parse_args(t_env *env, int argc, char **argv)
{
	env->philo_count = check_and_parse(argv[1]);
	env->time_to_die = check_and_parse(argv[2]);
	env->time_to_eat = check_and_parse(argv[3]);
	env->time_to_sleep = check_and_parse(argv[4]);
	if (argc == 6)
		env->max_meals = check_and_parse(argv[5]);
	else
		env->max_meals = -1;
	if (
		env->philo_count < 1
		|| env->philo_count > 200
		|| env->time_to_die < 0
		|| env->time_to_eat < 60
		|| env->time_to_sleep < 60
		|| (argc == 6 && env->max_meals < 0)
	)
		return (1);
	return (0);
}
