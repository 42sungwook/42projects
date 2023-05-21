#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				nb_need_eat;
	int				is_dead;
	int				nb_of_init;
	long			start_time;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*init;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
}					t_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	long			eat_time;
	long			eat_start;
}					t_philo;

int		ft_atoi(const char *str);
int		ft_init_mutex(t_data *data);
int		ft_init_thread(t_data *data, t_philo *philo);
int		ft_init_philo(t_data *data, int argc, char **argv);
void	*ft_routine(t_philo *philo);
size_t	ft_strlen(const char *s);
long	ft_get_time(void);
int		ft_strcmp(const char *s1, const char *s2);


#endif
