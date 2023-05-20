#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				nb_eat;
	int				is_dead;
	long			start_time;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
}					t_data;

int		ft_atoi(const char *str);
int		print_error(t_data *philo, char *str);
long	ft_get_time(void);
int		ft_init_philo(t_data *data, int argc, char **argv);

#endif