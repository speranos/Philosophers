#include "philo.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	sign = 1;
	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			res = res * 10 + (str[i] - 48);
		else
			break ;
		i++;
	}
	return (res * sign);
}

void	ft_usleep(int ms)
{
	long	time;

	time = gettime();
	while (gettime() < (time + ms))
		usleep(100);
}

long	gettime(void)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	ret = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (ret);
}

void	print_msg(t_data *ph_data, char c)
{
	long	time;

	pthread_mutex_lock(ph_data->print.print);
	time = gettime() - ph_data->start_time;
	if (c == 'e')
		printf("%ld philo %d is eating\n", time, ph_data->id);
	if (c == 's')
		printf("%ld philo %d is sleeping\n", time, ph_data->id);
	if (c == 't')
		printf("%ld philo %d is thinking\n", time, ph_data->id);
	if (c == 'r')
		printf("%ld philo %d has taken his fork\n", time, ph_data->id);
	if (c == 'l')
		printf("%ld philo %d has taken a fork\n", time, ph_data->id);
	if (c == 'k')
		printf("%ld philo %d Dead\n", time, ph_data->id);
	pthread_mutex_unlock(ph_data->print.print);
}

void	check_things(t_data *ph_data)
{
	long	time;

	while (1)
	{
		pthread_mutex_lock(ph_data->print.supra);
		time = (gettime() - ph_data->start_time) - ph_data->last_meal;
		if (time > ph_data->to_die)
		{
			pthread_mutex_lock(ph_data->print.print);
			time = gettime() - ph_data->start_time;
			printf("%ld philo %d Dead\n", time, ph_data->id);
			return ;
		}
		pthread_mutex_unlock(ph_data->print.supra);
		if (ph_data->eat_or_not == 1)
		{
			pthread_mutex_lock(ph_data->print.lock_eat);
			if (ph_data->is_eating == 0)
				return ;
			pthread_mutex_unlock(ph_data->print.lock_eat);
		}
	}
}
