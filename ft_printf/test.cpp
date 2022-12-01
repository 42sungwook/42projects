#include <stdio.h>
#include <limits.h>

int main()
{
	int	i;
	i = printf("%p", LONG_MIN);
	printf("\n%d", i);
}