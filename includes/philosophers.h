
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define BOOL				char
# define ERR_THRD_CREATE	"Failed at creating a new thread"
# define ERR_MALLOC			"Failer at allocating memory"
# define ERR_FEW_ARGS		"Missing argument(s)"
# define ERR_MANY_ARGS		"Too many arguments"
# define ERR_INV_ARGS		"Invalid argument(s)"
# define THINKING			0
# define TAKEN_FORK			1
# define EATING				2
# define SLEEPING			3
# define DEAD				4
# define RED                "\033[1;31m"
# define GREEN              "\033[1;32m"
# define WHITE              "\033[1;37m"
# define NO_COLOR           "\033[0m"

typedef long long t_ll;
typedef unsigned long long t_ull;

typedef struct s_philo
{
	struct s_env	*env;
	int				id;
	BOOL			status;
	unsigned		dead_time;
	unsigned		eat_count;
	t_ull			last_meal_time;
	pthread_mutex_t	eat_mutex;
}					t_philo;

typedef struct 			s_env
{
	BOOL				dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		logger;
	t_philo				*philos;
	t_ull				start_time;
	long				philo_count;
	long				time_to_eat;
	t_ull				time_to_die;
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
void		clean_data(t_env *env);

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

t_ll		str_to_int(char *s);
t_ll		check_and_parse(char *s);
BOOL		parse_args(t_env *env, int argc, char **argv);

/*
** time utils
*/

t_ll		time_now();
void		usleep_wrapper(unsigned time);

/*
** print utils
*/

void		print_status(t_philo *ph, BOOL status);
BOOL		print_error(char *msg);
void		put_str(int fd, char *s);
size_t		str_len(char *s);

#endif
