#include "vm.h"

void	ft_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
