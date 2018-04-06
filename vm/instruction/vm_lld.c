/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/06 10:28:04 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_lld_perm(char perm[3][3])
{
	perm[0][0] = 0;
	perm[0][1] = 1;
	perm[0][2] = 1;
	perm[1][0] = 1;
	perm[1][1] = 0;
	perm[1][2] = 0;
}

void			vm_lld(t_process *process, t_vm *env)
{
	char			perm[3][3];
	t_param			param;
	char			peb;

	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	get_lld_perm(perm);
	param.mod = L_DIR | IND_TARG;
	param.len = param_len(peb, 1, 2) + 2;
	if (!check_peb(peb, perm, 2))
	{
		get_param(&param, process, env);
		if (!check_reg(peb, 2, &param))
		{
			process->reg[param.two - 1] = param.one;
			process->carry = !(param.one) ? 1 : 0;
		}
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + param.len, param.len, env);
	process->pc += param.len;
}
