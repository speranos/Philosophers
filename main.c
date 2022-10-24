#include "philo.h"

int	ft_check_type(int ac, char **av)
{
	int	i;

	i = 0;
	ac--;
	while (ac > 1)
	{
		i = 0;
		while (av[ac][i])
		{
			if(av[ac][i] < 48 || av[ac][i] >  57)
				return (1);
			i++;
		}
		ac--; 
	}
	return (0);
	
}

int	ft_check_value(int ac, char **av)
{
	if (atoi(av[1]) <= 0)
		return (1);
	else if (atoi(av[2]) < 0)
		return (1);
	else if (atoi(av[3]) < 0)
		return (1);
	else if (atoi(av[4]) < 0)
		return (1);
	if (ac == 6)
	{
		if (atoi(av[5]) < 0)
			return (1);
	}
	return (0);
}

int	ft_arg_check(int ac, char **av)
{
	(void)av;
	if (ac < 5 || ac > 6)
	{
		printf("args...error !!!");
		return (1);
	}
	if (ft_check_type(ac,av))
	{
		printf ("error...only number !!!");
		return (1);
	}
	if (ft_check_value(ac, av) == 1)
	{
		printf ("args...value...error !!!");
		return (1);
	}
	return (0);
}

void *act_philo(void *philo_data)
{
	//int	i;
	data	*ph_data;

	ph_data = (data *)philo_data;
	//i = 0;
// while(1)
// {
	
	//printf("creat 9bal ====== %d\n", ph_data->creat);
	pthread_mutex_lock(&ph_data->mutex);
	//pthread_mutex_lock(&ph_data[(ph_data->creat % ph_data->ph_num) + 1].mutex);
	printf("philo num = %d ===> \n", ph_data->id);
	printf ("philo %p is eating\n", ph_data->philo);

	pthread_mutex_unlock(&ph_data->mutex);
	//pthread_mutex_unlock(&ph_data[(ph_data->creat % ph_data->ph_num) + 1].mutex);
	usleep(ph_data->to_eat);
	// if(ph_data->creat == ph_data->ph_num - 1)
	// {
	// 	ph_data->creat = 0;
	// 	ph_data->id = 1;
	// }
	//printf("creat after ====== %d\n", ph_data->creat);
	//i++;
	//printf("ma good ma ta 9alwa\n");
// }
	return(0);
}

void	ft_add(data *philo_data, char **av, int ac)
{
	int i;

	i = 0;
	while(i < ft_atoi(av[1]))
	{
		philo_data[i].ph_num = ft_atoi(av[1]);
		philo_data[i].to_die = ft_atoi(av[2]);
		philo_data[i].to_eat = ft_atoi(av[3]);
		philo_data[i].to_sleep = ft_atoi(av[4]);
		philo_data[i].id = i + 1;
		if(ac == 6)
			philo_data[i].eat = ft_atoi(av[5]);
		i++;
	}
	
}

void	ft_ph_creat(data *philo_data, char **av, int ac)
{
	int	i;
	int a;
	int x;

	//philo_data->creat = 1;
	a = 0;
	x = 0;
	i = 0;
	ft_add(philo_data, av, ac);
	while (i <= philo_data->ph_num)
	{
		pthread_mutex_init(&philo_data[i].mutex, NULL);
		//philo_data[i].mutex = malloc(sizeof(pthread_mutex_t));
		i++;
	}
	i = 0;
	while(i < philo_data->ph_num)
	{
		// philo_data[i].philo = malloc(sizeof(pthread_t));
		pthread_create(&philo_data[i].philo, NULL, act_philo, &philo_data[i]);
		usleep(100);
		philo_data->creat++;
		i++;
	}

	i = 0;
	while(i < philo_data->ph_num)
	{
		pthread_join(philo_data[i].philo, NULL);
		i++;
	}



	
}

int	main(int ac, char **av)
{
	data	*ph_data;

	ph_data = malloc(sizeof(data) * ft_atoi(av[1]));
	if (ft_arg_check(ac, av) == 1)
		return (0);
	else
		ft_ph_creat(ph_data, av, ac);
	printf ("all good\n");
}