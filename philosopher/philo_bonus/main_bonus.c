#include "philo_bonus.h"

static int	ft_error(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	if (data)
	{
		ft_free_data(data);
		free(data);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!(argc == 5 || argc == 6))
		return (ft_error(data, "Error: Invalid Arguments\n"));
	if (!data)
		return (1);
	if (ft_init_philo(data, argc, argv))
		return (ft_error(data, "Error: Invalid Argument Number\n"));
	return (0);
}
