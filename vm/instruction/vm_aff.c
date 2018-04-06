/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/06 10:13:53 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_aff_perm(char perm[3][3])
{
	perm[0][0] = 1;
	perm[0][1] = 0;
	perm[0][2] = 0;
}

void			vm_aff(t_process *process, t_vm *env)
{
	char			perm[3][3];
	t_param			param;
	char			peb;

	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	get_aff_perm(perm);
	param.mod = 0;
	param.len = param_len(peb, 1, 1) + 2;
	if (!check_peb(peb, perm, 1))
	{
		get_param(&param, process, env);
		if (!check_reg(peb, 1, &param))
			ft_putchar((unsigned char)process->reg[param.one - 1]);
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + param.len, param.len, env);
	process->pc += param.len;
}
