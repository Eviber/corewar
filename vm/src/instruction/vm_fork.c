/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:26:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/28 20:31:30 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_fork(t_process *process, t_vm *env)
{
	short			param;
	unsigned int	new_pc;

	param = ((short)env->memory[process->pc + 1]) << 8;
	param += ((short)env->memory[process->pc + 2]);
	new_pc = process->pc + (param % IDX_MOD);
	add_process(&env->process, new_process(process, new_pc, env));
	env->process->inst = -1;
	(env->nb_process)++;
	process->pc += 3;
}
