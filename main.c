#include "philo.h"

int	ft_supra(t_data *philo_data)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < philo_data->ph_num)
	{
		pthread_mutex_lock(philo_data->print.done);
		if (philo_data[i].num_of_meal >= philo_data->eat)
			cnt++;
		pthread_mutex_unlock(philo_data->print.done);
		i++;
	}
	if (cnt == philo_data->ph_num)
		return (1);
	return (0);
}

void	ft_check_meal(t_data *ph_data)
{
	if (ph_data->eat_or_not == 1)
	{
		pthread_mutex_lock(ph_data->print.done);
		ph_data->num_of_meal++;
		pthread_mutex_unlock(ph_data->print.done);
		if (ft_supra(ph_data))
		{
			pthread_mutex_lock(ph_data->print.lock_eat);
			ph_data->is_eating = 0;
			pthread_mutex_unlock(ph_data->print.lock_eat);
		}
	}
}

void	*act_philo(void *philo_data)
{
	t_data	*ph_data;

	ph_data = (t_data *)philo_data;
	while (1)
	{
		pthread_mutex_lock(&ph_data->print.fork[ph_data->left]);
		print_msg(ph_data, 'r');
		pthread_mutex_lock(&ph_data->print.fork[ph_data->right]);
		print_msg(ph_data, 'l');
		print_msg(ph_data, 'e');
		pthread_mutex_lock(ph_data->print.supra);
		ph_data->last_meal = gettime() - ph_data->start_time;
		pthread_mutex_unlock(ph_data->print.supra);
		ft_usleep(ph_data->to_eat);
		ft_check_meal(ph_data);
		pthread_mutex_unlock(&ph_data->print.fork[ph_data->left]);
		pthread_mutex_unlock(&ph_data->print.fork[ph_data->right]);
		print_msg(ph_data, 's');
		ft_usleep(ph_data->to_sleep);
		print_msg(ph_data, 't');
	}
	return (0);
}

void	ft_ph_creat(t_data *philo_data, char **av, int ac)
{
	int	i;

	i = 0;
	ft_add(philo_data, av, ac);
	ft_mutex_init(philo_data);
	while (i < philo_data->ph_num)
	{
		pthread_create(&philo_data[i].philo, NULL, act_philo, &philo_data[i]);
		i = i + 2;
	}
	usleep(50);
	i = 1;
	while (i < philo_data->ph_num)
	{
		pthread_create(&philo_data[i].philo, NULL, &act_philo, &philo_data[i]);
		i = i + 2;
	}
}

int	main(int ac, char **av)
{
	t_data	*ph_data;

	if (ft_arg_check(ac, av) == 1)
		return (0);
	else
	{
		ph_data = malloc(sizeof(t_data) * ft_atoi(av[1]));
		ft_ph_creat(ph_data, av, ac);
	}
	check_things(ph_data);
	return (0);
}
