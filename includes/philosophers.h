
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define BOOL			char
# define ERR_FEW_ARGS	"missing argument(s)"
# define ERR_MANY_ARGS	"Too many arguments"
# define THINKING		0
# define TAKEN_FORK		1
# define EATING			2
# define SLEEPING		3
# define DEAD			4

// typedef struct foo
// {
// 	char x:1;
// }		foo;

typedef unsigned long	t_ul;

typedef struct s_philo
{
	struct s_env	*env;
	int				id;
	BOOL			status;
	unsigned		dead_time;
	unsigned		eat_count;
	t_ul			last_meal_time;
	// pthread_mutex_t	eat_mutex;
}					t_philo;

typedef struct 			s_env
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		logger;
	t_philo				*philos;
	unsigned			start_time;
	unsigned			philo_count;
	unsigned			time_to_eat;
	unsigned			time_to_die;
	unsigned			time_to_sleep;
	unsigned			meal_time;
	unsigned			max_meals;
}						t_env;

void		create_threads(t_env *env);
void		*run_simulation(void *philo);
void		print_status(t_philo *ph, BOOL status);
void		thinking(t_philo *ph);
void		eating(t_philo *ph);
void		take_forks(t_philo *ph);
void		put_forks(t_philo *ph);
void		sleeping(t_philo *ph);
void		died(t_philo *ph);
unsigned	time_now();

#endif
