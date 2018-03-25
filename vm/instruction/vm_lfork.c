/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:26:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/25 13:58:34 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			vm_lfork(t_process *process, t_vm *env)
{
	short			param;
	unsigned int	new_pc;

	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + 3, 3, env);
	param = ((short)env->memory[(process->pc + 1) % MEM_SIZE]) << 8;
	param += ((short)env->memory[(process->pc + 2) % MEM_SIZE]);
	new_pc = process->pc + param;
	add_process(&env->process, new_process(process, new_pc, env));
	env->process->inst = -1;
	(env->process->champ->nb_process)++;
	(env->nb_process)++;
	process->pc += 3;
}
