/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:19:53 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/28 17:28:18 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_cooldown(t_process *process, t_vm *env)
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
	if (env->memory[process->pc % MEM_SIZE] <= 16 && \
	env->memory[process->pc % MEM_SIZE] > 0)
		process->cooldown = nb_cycle[process->inst - 1];
	else
		process->cooldown = 0;
}

void	exec_process(t_process *process, t_op *op_tab, t_vm *env)
{
	if (process->inst == -1)
	{
		process->inst = env->memory[process->pc % MEM_SIZE];
		set_cooldown(process, env);
	}
	(process->cooldown)--;
	if (!process->cooldown && process->inst <= 16 && process->inst > 0)
	{
		op_tab[process->inst - 1](process, env);
		process->inst = -1;
	}
	else if (process->cooldown <= 0)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
		process->inst = env->memory[process->pc];
		set_cooldown(process, env);
	}
	process->pc = process->pc % MEM_SIZE;
}
