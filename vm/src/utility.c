#include "vm.h"

void	ft_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	write_memory(unsigned int value, unsigned int address, t_vm *env)
{
	int				i;
	unsigned char	tmp[4];

	i = -1;
	tmp[0] = value >> 24;
	tmp[1] = value >> 16 & 255;
	tmp[2] = value >> 8 & 255;
	tmp[3] = value & 255;
	while (++i < 4)
		env->memory[address + i] = tmp[i];
}
