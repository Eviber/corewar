#include "vm.h"
#include "visu.h"

void			ft_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void			write_memory(unsigned int value, unsigned int address,
							t_vm *env, t_header *champ)
{
	env->memory[address % MEM_SIZE] = value >> 24;
	env->memory[(address + 1) % MEM_SIZE] = value >> 16 & 255;
	env->memory[(address + 2) % MEM_SIZE] = value >> 8 & 255;
	env->memory[(address + 3) % MEM_SIZE] = value & 255;
	putinvisu(address, champ);
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

void *ft_memalloc_exit(size_t size)
{
	void *mem;
	if (!(mem = ft_memalloc(size)))
	{
		ft_dprintf(2, "Malloc has failed in this execution\n");
		exit(1);
	}
	return(mem);
}
