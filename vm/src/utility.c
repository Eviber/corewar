#include "vm.h"

void			ft_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void			write_memory(unsigned int value, unsigned int address, t_vm *env)
{
	env->memory[address % MEM_SIZE] = value >> 24;
	env->memory[(address + 1) % MEM_SIZE] = value >> 16 & 255;
	env->memory[(address + 2) % MEM_SIZE] = value >> 8 & 255;
	env->memory[(address + 3) % MEM_SIZE] = value & 255;
}

unsigned int	read_memory(unsigned int address, t_vm *env)
{
	unsigned int	value;

	value = env->memory[address % MEM_SIZE] << 24;
	value += env->memory[(address + 1) % MEM_SIZE] << 16;
	value += env->memory[(address + 2) % MEM_SIZE] << 8;
	value += env->memory[(address + 3) % MEM_SIZE];
	return (value);
}
