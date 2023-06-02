/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:25:32 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/02 23:25:24 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_free_data(t_data *data)
{
	if (data->fork)
	{
		sem_close(data->fork);
		sem_close(data->print);
		sem_unlink("fork");
		sem_unlink("print");
	}
	free(data);
}

static int	ft_error(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	if (data)
		ft_free_data(data);
	return (1);
}

static void	ft_main_process(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (data->pid[i] != pid)
			kill(data->pid[i], SIGKILL);
	}
	i = -1;
	while (++i < data->nb_of_philo - 1)
		waitpid(-1, &status, 0);
	sem_post(data->print);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!(argc == 5 || argc == 6))
		return (ft_error(data, "Error: Invalid Arguments\n"));
	if (!data)
		return (1);
	if (ft_init_philo(data, argc, argv))
		return (ft_error(data, "Error: Invalid Argument Number\n"));
	if (ft_init_sem(data))
		return (ft_error(data, "Error: Semaphore Init Error\n"));
	if (ft_init_process(data))
		return (ft_error(data, "Error: Process Init Error\n"));
	ft_main_process(data);
	ft_free_data(data);
	return (0);
}
