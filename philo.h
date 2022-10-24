#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

typedef struct philo_data
{
	pthread_t	philo;
	pthread_mutex_t mutex;
	int			ph_num;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			eat;
	int			id;
	int			creat;

}   data;

void	ft_ph_creat(data *philo_data, char **av, int ac);
int		ft_atoi(char *str);

#endif