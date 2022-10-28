#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
typedef struct s_print
{
	pthread_mutex_t print;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	supra;
	int 			done;
}		t_print;


typedef struct philo_data
{
	pthread_t	philo;
	// pthread_mutex_t mutex;
	pthread_mutex_t	*fork;
	time_t			start_time;
	int			ph_num;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			eat;
	int			id;
	int			creat;
	int			right;
	int			left;
	long		last_meal;
	int			eat_or_not;
	int			num_of_meal;
	t_print 	print;

}   data;

void	ft_ph_creat(data *philo_data, char **av, int ac);
int		ft_atoi(char *str);
long 	gettime(void);

#endif