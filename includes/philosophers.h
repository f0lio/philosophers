
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h> // ?
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define BOOL				char
# define ERR_THRD_CREATE	"Failed at creating a new thread"
# define ERR_FEW_ARGS		"Missing argument(s)"
# define ERR_MANY_ARGS		"Too many arguments"
# define ERR_INV_ARGS		"Invalid argument(s)"
# define THINKING			0
# define TAKEN_FORK			1
# define EATING				2
# define SLEEPING			3
# define DEAD				4

typedef unsigned long long t_ul;

typedef struct s_philo
{
	struct s_env	*env;
	int				id;
	BOOL			status;
	unsigned		dead_time;
	unsigned		eat_count;
	t_ul			last_meal_time;
	pthread_mutex_t	eat_mutex;
}					t_philo;

typedef struct 			s_env
{
	BOOL				dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		logger;
	t_philo				*philos;
	unsigned long long	start_time;
	long				philo_count;
	long				time_to_eat;
	long				time_to_die;
	long				time_to_sleep;
	long				meal_time;
	long				max_meals;
}						t_env;

/*
** Simulation
*/

BOOL		start_simulation(t_env *env);
BOOL		create_threads(t_env *env);
void		*philo_routine(void *philo);
void		supervise(t_env *env);

/*
** Philosopher's states
*/

void		thinking(t_philo *ph);
void		eating(t_philo *ph);
void		take_forks(t_philo *ph);
void		put_forks(t_philo *ph);
void		sleeping(t_philo *ph);
void		died(t_philo *ph);

/*
** Parser
*/

int			str_to_int(char *s);
int			check_and_parse(char *s);
BOOL		parse_args(t_env *env, int argc, char **argv);

/*
** time utils
*/

unsigned
long	long	time_now();
void		usleep_wrapper(unsigned time);

/*
** print utils
*/

void		print_status(t_philo *ph, BOOL status);
void		print_long(long l);
BOOL		print_error(char *msg);
void		put_str(char *s);
void		put_char(char c);
size_t		str_len(char *s);

#endif
