/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:19:53 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/17 23:05:38 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		set_cooldown(t_process *process)
{
	unsigned int	nb_cycle[16];

	nb_cycle[0] = 10;
	nb_cycle[1] = 5;
	nb_cycle[2] = 5;
	nb_cycle[3] = 10;
	nb_cycle[4] = 10;
	nb_cycle[5] = 6;
	nb_cycle[6] = 6;
	nb_cycle[7] = 6;
	nb_cycle[8] = 20;
	nb_cycle[9] = 25;
	nb_cycle[10] = 25;
	nb_cycle[11] = 800;
	nb_cycle[12] = 10;
	nb_cycle[13] = 50;
	nb_cycle[14] = 1000;
	nb_cycle[15] = 2;
	process->cooldown = nb_cycle[process->inst[0] - 1];
}

void			exec_process(t_process *process, t_op op_tab, t_vm *env)
{
	if (!(--(process->cooldown)) && inst[0] <= 16 && inst[0] > 0)
		op_tab[inst[0] - 1](process, env);
	else if (!process->cooldown)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		ft_memcpy((void*)process->inst, (void*)&(env->memory[process->pc]), 16);
		if (env->memory[process->pc] <= 16 && env->memory[process->pc] > 0)
			set_cooldown(process);
	}
}
