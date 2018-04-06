/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/06 10:05:36 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_add_perm(char perm[3][3])
{
	perm[0][0] = 1;
	perm[0][1] = 0;
	perm[0][2] = 0;
	perm[1][0] = 1;
	perm[1][1] = 0;
	perm[1][2] = 0;
	perm[2][0] = 1;
	perm[2][1] = 0;
	perm[2][2] = 0;
}

void			vm_add(t_process *process, t_vm *env)
{
	char			perm[3][3];
	t_param			param;
	char			peb;

	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	get_add_perm(perm);
	param.mod = 0;
	param.len = param_len(peb, 1, 3) + 2;
	if (!check_peb(peb, perm, 3))
	{
		get_param(&param, process, env);
		if (!check_reg(peb, 3, &param))
		{
			process->reg[param.thr - 1] = process->reg[param.one - 1] +\
			process->reg[param.two - 1];
			process->carry = !(process->reg[param.thr - 1]) ? 1 : 0;
		}
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + param.len, param.len, env);
	process->pc += param.len;
}
