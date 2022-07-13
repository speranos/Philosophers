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

int	main(int ac, char **av)
{
	if (ft_arg_check(ac, av) == 1)
		return (0);
	printf ("all good\n");
}