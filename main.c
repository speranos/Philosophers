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

void	ft_usleep(unsigned int tms)
{
	 long	old_time;

	old_time = gettime();
	usleep(tms - 30000);
	while (gettime() < old_time + tms / 1000)
		;
}

// void	ft_usleep(int ms)
// {
// 	long	time;

// 	time = gettime();

// 	while(gettime() < (time + ms))
// 		usleep(100);
// }

long gettime(void)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	ret = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec  / 1000;
	return(ret);
}
void print_msg (data *ph_data , char c)
{
	pthread_mutex_lock(&ph_data->print.print);
	if (c == 'e')
		printf("{%ld} philo %d is eating\n", gettime() - ph_data->start_time, ph_data->id );
	if (c == 's')
		printf("{%ld} philo %d is sleeping\n", gettime() - ph_data->start_time, ph_data->id );
	if (c == 't')
		printf("{%ld} philo %d is thinking\n", gettime() - ph_data->start_time, ph_data->id );
	if (c == 'f')
		printf("{%ld} philo %d has taken a fork\n", gettime() - ph_data->start_time, ph_data->id );
	pthread_mutex_unlock(&ph_data->print.print);
}

void *act_philo(void *philo_data)
{
	data	*ph_data;
	// pthread_mutex_t print;

	// pthread_mutex_init(&print, NULL);
	ph_data = (data *)philo_data;
	
while(1)
{
	int next_fork;
	
		
	next_fork = ph_data->id  % ph_data->ph_num + 1;	
	pthread_mutex_lock(&ph_data->fork);
	pthread_mutex_lock(&ph_data[next_fork - 1 ].fork);
	print_msg(ph_data, 'f');
	print_msg(ph_data, 'f');
	print_msg(ph_data, 'e');
	ft_usleep(1000 * ph_data->to_eat);
	pthread_mutex_unlock(&ph_data->fork);
	pthread_mutex_unlock(&ph_data[next_fork - 1 ].fork);
	print_msg(ph_data, 's');
	ft_usleep(1000 * ph_data->to_sleep);
	print_msg(ph_data, 't');
	
 }
	return(0);
}

void	ft_add(data *philo_data, char **av, int ac)
{
	int i;

	i = 0;
	while(i < ft_atoi(av[1]))
	{
		philo_data[i].start_time = gettime();
		philo_data[i].ph_num = ft_atoi(av[1]);
		philo_data[i].to_die = ft_atoi(av[2]);
		philo_data[i].to_eat = ft_atoi(av[3]);
		philo_data[i].to_sleep = ft_atoi(av[4]);
		philo_data[i].id = i + 1;
		if(ac == 6)
			philo_data[i].eat = ft_atoi(av[5]);
		i++;
	}
	printf("id ======== %d\n", philo_data[i - 1].id);
	//printf
	
}

void	ft_ph_creat(data *philo_data, char **av, int ac)
{
	int	i;
	// int j;

	//philo_data->creat = 1;
	// j = 1;
	i = 0;
	ft_add(philo_data, av, ac);
	pthread_mutex_init(&philo_data->print.print , NULL);
	while (i < philo_data->ph_num)
	{
		// pthread_mutex_init(&philo_data[i].mutex, NULL);
		pthread_mutex_init(&philo_data[i].fork, NULL);
		i++;
	}
	i = 0;
	while(i < philo_data->ph_num)
	{
		pthread_create(&philo_data[i].philo, NULL, act_philo, &philo_data[i]);
		// usleep(100);
		//philo_data->creat++;
		i = i+2;
	}
	usleep(500);
	i = 1;
	while(i < philo_data->ph_num)
	{
		pthread_create(&philo_data[i].philo, NULL, act_philo, &philo_data[i]);
		// usleep(100);
		//philo_data->creat++;
		i = i+2;
	}
	// i = 0;
	// while(i < philo_data->ph_num)
	// {
	// 	pthread_join(philo_data[i].philo, NULL);
	// 	i++;
	// }
}

int	main(int ac, char **av)
{
	data	*ph_data;

	ph_data = malloc(sizeof(data) * ft_atoi(av[1]));
	if (ft_arg_check(ac, av) == 1)
		return (0);
	else
		ft_ph_creat(ph_data, av, ac);
	while(1)
	{

	}

	printf ("all good\n");
}