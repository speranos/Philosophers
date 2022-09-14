#include <stdio.h>
#include <unistd.h>

int i = 0;

void ingr()
{
	int a = 0;
	while (a < 1000000)
	{
		i++;
		a++;
	}
	printf("a >>>>>>> %d\n", a);
	printf("KDA\n");
	sleep(3);
//	return(0);
}

int main(int ac, char **av)
{
	while(ac > 0)
	{
		ingr();
		ac--;
	}
	printf("i >>>>>>>>> %d\n", i);
}
