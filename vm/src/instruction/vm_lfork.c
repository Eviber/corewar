/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:26:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/25 00:00:16 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			vm_lfork(t_process *process, t_vm *env)
{
	short			param;
	unsigned int	new_pc;

	param = ((short)env->memory[process->pc + 1]) << 8;
	param += ((short)env->memory[process->pc + 2]);
	new_pc = process->pc + param;
	add_process(&env->process, new_process(process, new_pc, env));
	env->process->inst = env->memory[env->process->pc];
	set_cooldown(env->process, env);
}
