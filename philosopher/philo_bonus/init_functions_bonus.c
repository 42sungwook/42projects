/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:25:29 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/02 22:31:58 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_sem(t_data *data)
{
	sem_unlink("fork");
	data->fork = sem_open("fork", O_CREAT | O_EXCL, 0644, \
		data->nb_of_philo);
	if (data->fork == SEM_FAILED)
		return (1);
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (1);
	sem_unlink("init");
	data->init = sem_open("init", O_CREAT | O_EXCL, 0644, \
		data->nb_of_philo);
	if (data->init == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_init_philo(t_data *data, int argc, char **argv)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_slp = ft_atoi(argv[4]);
	if (data->nb_of_philo < 1 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_slp < 0)
		return (1);
	data->nb_need_eat = -1;
	data->nb_end_eat = 0;
	data->id = 0;
	data->eat_num = 0;
	data->eat_start = 0;
	data->nb_of_init = 0;
	data->start_time = 0;
	if (argc == 6)
	{
		data->nb_need_eat = ft_atoi(argv[5]);
		if (data->nb_need_eat < 0)
			return (1);
	}
	return (0);
}
