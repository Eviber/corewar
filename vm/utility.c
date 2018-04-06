/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:27:31 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/06 11:17:54 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (env->option->visu)
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

void			destroy_env(t_vm *env, t_op *op_tab)
{
	t_process	*next_p;
	t_header	*next_c;

	ft_memdel((void**)&env->option);
	while (env->killed_process)
	{
		next_p = env->killed_process->next;
		ft_memdel((void**)&env->killed_process);
		env->killed_process = next_p;
	}
	while (env->champion)
	{
		next_c = env->champion->next;
		ft_memdel((void**)&env->champion);
		env->champion = next_c;
	}
	ft_memdel((void**)&env);
	ft_memdel((void**)&op_tab);
}
