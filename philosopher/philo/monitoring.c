#include "philo.h"

int	ft_monitoring(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(data->print);
		if (philo->eat_start && ft_get_time() - \
			philo->eat_start > data->time_to_die)
		{
			data->is_dead = 1;
			printf("%ld %d is dead\n", ft_get_time() - \
			data->start_time, philo->id + 1);
			pthread_mutex_unlock(data->print);
			return (1);
		}
		pthread_mutex_unlock(data->print);
		philo++;
		i++;
	}
	return (0);
}
