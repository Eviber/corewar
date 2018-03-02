/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:26:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/02 15:53:06 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_fork(t_process *process, t_vm *env)
{
	short			param;
	unsigned int	new_pc;

	if ((env->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + 3, 3, env);
	param = ((short)env->memory[process->pc + 1]) << 8;
	param += ((short)env->memory[process->pc + 2]);
	new_pc = process->pc + (param % IDX_MOD);
	add_process(&env->process, new_process(process, new_pc));
	env->process->inst = -1;
	(env->nb_process)++;
	process->pc += 3;
}
