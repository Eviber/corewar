/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/06 10:28:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_lldi_perm(char perm[3][3])
{
	perm[0][0] = 1;
	perm[0][1] = 1;
	perm[0][2] = 1;
	perm[1][0] = 1;
	perm[1][1] = 1;
	perm[1][2] = 0;
	perm[2][0] = 1;
	perm[2][1] = 0;
	perm[2][2] = 0;
}

void			vm_lldi(t_process *prc, t_vm *env)
{
	char			perm[3][3];
	t_param			p;
	char			peb;

	peb = env->memory[(prc->pc + 1) % MEM_SIZE];
	get_lldi_perm(perm);
	p.mod = IND_TARG | IMOD;
	p.len = param_len(peb, 0, 3) + 2;
	if (!check_peb(peb, perm, 3))
	{
		get_param(&p, prc, env);
		if (!check_reg(peb, 3, &p))
		{
			if (PARAM_ONE(peb) == REG_CODE)
				p.one = prc->reg[p.one - 1];
			if (PARAM_TWO(peb) == REG_CODE)
				p.two = prc->reg[p.two - 1];
			prc->reg[p.thr - 1] = read_memory(prc->pc + p.one + p.two, env);
			prc->carry = !(prc->reg[p.thr - 1]) ? 1 : 0;
		}
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(prc->pc, prc->pc + p.len, p.len, env);
	prc->pc += p.len;
}
