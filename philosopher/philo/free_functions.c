/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:43:17 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/29 17:14:15 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_free(pthread_mutex_t *temp)
{
	pthread_mutex_destroy(temp);
	free(temp);
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->fork)
	{
		while (i < data->nb_of_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		free(data->fork);
	}
	if (data->philo_thread)
		free(data->philo_thread);
	if (data->init)
		ft_destroy_free(data->init);
	if (data->print)
		ft_destroy_free(data->print);
	if (data->dead)
		ft_destroy_free(data->dead);
	if (data->eat)
		ft_destroy_free(data->eat);
	if (data)
		free(data);
}
