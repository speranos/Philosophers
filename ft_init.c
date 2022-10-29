#include "philo.h"

void	ft_mutex_init(data *ph_data)
{
	int	i;

	i = 0;
	ph_data->print.fork = malloc(sizeof(pthread_mutex_t) * ph_data->ph_num);
	pthread_mutex_init(&ph_data->print.print, NULL);
    pthread_mutex_init(&ph_data->print.supra, NULL);
	while (i < ph_data->ph_num)
	{
		pthread_mutex_init(&ph_data->print.fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < ph_data->ph_num)
	{
		ph_data[i].print.fork = ph_data->print.fork;
		i++;
	}
}

void	ft_add(data *philo_data, char **av, int ac)
{
	int	i;

	i = 0;
	philo_data[i].eat_or_not = 0;
	philo_data->is_eating = 0;
	while (i < ft_atoi(av[1]))
	{
		philo_data[i].start_time = gettime();
		philo_data[i].ph_num = ft_atoi(av[1]);
		philo_data[i].to_die = ft_atoi(av[2]);
		philo_data[i].to_eat = ft_atoi(av[3]);
		philo_data[i].to_sleep = ft_atoi(av[4]);
		philo_data[i].id = i + 1;
		philo_data[i].num_of_meal = 0;
		if (ac == 6)
		{
			philo_data[i].eat = ft_atoi(av[5]);
			philo_data[i].eat_or_not = 1;
			philo_data->is_eating = 1;
		}
		philo_data[i].left = i;
		philo_data[i].right = (i + 1) % philo_data->ph_num;
		i++;
	}
}