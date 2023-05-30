#include "philo_bonus.h"

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
	if (argc == 6)
	{
		data->nb_need_eat = ft_atoi(argv[5]);
		if (data->nb_need_eat < 0)
			return (1);
	}
	return (0);
}