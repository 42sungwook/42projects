/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:25:35 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/03 16:32:52 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_data
{
	int			nb_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_slp;
	int			nb_need_eat;
	int			nb_end_eat;
	int			id;
	int			eat_num;
	int			nb_of_init;
	long		start_time;
	long		eat_start;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*init;
	pid_t		*pid;
}					t_data;

long	ft_get_time(void);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_init_philo(t_data *data, int argc, char **argv);
int		ft_init_sem(t_data *data);
int		ft_init_process(t_data *data);
void	ft_one_philo_process(t_data *data);

#endif
