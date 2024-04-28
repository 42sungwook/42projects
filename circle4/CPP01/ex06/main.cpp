#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl harl;

	if (ac < 2)
		return 0;
	for (int i = 1; i < ac; ++i)
		harl.complain(av[i]);
	return 0;
}