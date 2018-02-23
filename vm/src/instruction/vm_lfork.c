/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:26:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 18:21:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			lfork(t_process *process, t_vm *env)
{
	int				param;
	unsigned int	new_pc;

	param = ((int)env->memory[process->pc + 1]) << 8;
	param += param | ((int)env->memory[process->pc + 2]);
	if (param & 0b00000000000000001000000000000000)
		param = -(param & 0b00000000000000000111111111111111);
	new_pc = process->pc + param;
	add_process(env->process, new_process(process, new_pc, env));
	env->process->inst = env->memory[env->process->pc];
	set_cooldown(env->process, env);
	env->process->last_live = env->cycle;
}
