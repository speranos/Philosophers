#include "philo.h"

int	ft_atoi(char *str)
{
    int	k;
    int	sign;
    int	res;
	int i;

	k = 0;
	sign = 1;
	res = 0;
	i = 0;
	while(str[i] <= 32)
		i++;
	while(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			{
				sign = -1;
				k++;
			}
		else
			k++;
		i++;
	}
	if(k > 1)
		return(0);
	while(str[i])
	{
		if(str[i] >= 48 && str[i] <= 57)
			res = res * 10 + (str[i] - 48);
		else
			break;
		i++;
	}
	return(res * sign);
}