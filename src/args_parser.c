
#include "philosophers.h"

int	str_to_int(char *s)
{
	return (atoi(s));

}

int	check_and_parse(char *s)
{
	while (*s)
		if (*s >= '0' && *s <= '9')
			s++;
		else
			return (-1);
	return (str_to_int(s));
}

BOOL	parse_args(t_env *env, int argc, char **argv)
{
	env->philo_count = str_to_int(argv[1]);
	env->time_to_die = str_to_int(argv[2]);
	env->time_to_eat = str_to_int(argv[3]);
	env->time_to_sleep = str_to_int(argv[4]);
	if (argc == 6)
		env->max_meals = str_to_int(argv[5]);
	else
		env->max_meals = -1;
	// if (
	// 	env->philo_count < 1 || env->philo_count > 200
	// 	|| env->time_to_die < 60
	// 	|| env->time_to_eat < 60
	// 	|| env->time_to_sleep < 100  //? 
	// 	|| (argc == 6 && env->max_meals < 0)
	// )
	// 	return (print_error(ERR_INV_ARGS));
	return (0);
}