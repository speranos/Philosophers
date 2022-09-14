#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	mutex;

void    *doso(void	*thread)
{
	int i = 0;
	long	*tid  = (long *) thread;
	printf("TID ========== %ld\n", *tid);
	pthread_mutex_lock(&mutex);
	printf("philo: %ld is eating\n", *tid);
	sleep(5);
	pthread_mutex_unlock(&mutex);
	printf("philo: %ld is waiting\n", *tid);
	sleep(2);
	printf("philo: %ld is sleeping\n", *tid);
	sleep(4);
	printf("philo: %ld is thinking\n", *tid);
	sleep(3);
	printf("philo: %ld is dying\n", *tid);

    return(0);
}

int main(int ac, char **av)
{
    (void)av;
    pthread_t *thread;
	int	i;
	int tmp;

	i = 0;
	tmp = ac;
	pthread_mutex_init(&mutex, NULL);
    thread = malloc(sizeof(pthread_t) * ac);
    while (tmp > 0)
    {
        pthread_create(&thread[i], NULL, &doso, (void*) &thread[i]);
        tmp--;
		i++;
    }
	i = 0;
	tmp = ac;
	while (tmp > 0)
	{
    	pthread_join(thread[i], NULL);
		i++;
		tmp--;
	}

}