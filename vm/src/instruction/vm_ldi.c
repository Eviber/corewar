/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/02 15:53:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_ldi_perm(void)
{
	char	**perm;

	if (!(perm = (char**)ft_memalloc(sizeof(char*) * 3)))
		ft_exit(strerror(errno));
	if (!(perm[0] = ft_strnew(2)))
		ft_exit(strerror(errno));
	if (!(perm[1] = ft_strnew(2)))
		ft_exit(strerror(errno));
	if (!(perm[2] = ft_strnew(2)))
		ft_exit(strerror(errno));
	perm[0][0] = 1;
	perm[0][1] = 1;
	perm[0][2] = 1;
	perm[1][0] = 1;
	perm[1][1] = 1;
	perm[1][2] = 0;
	perm[2][0] = 1;
	perm[2][1] = 0;
	perm[2][2] = 0;
	return (perm);
}

void			vm_ldi(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	char			peb;

	peb = env->memory[process->pc + 1];
	if (!perm)
		perm = get_ldi_perm();
	param.mod = IND_TARG | IMOD;
	if (!check_peb(peb, perm, 3))
	{
		get_param(&param, process, env);
		if ((env->verbose & SHOW_MOVE))
			show_pc_mov(process->pc, process->pc + param.len, param.len, env);
		if (!check_reg(peb, 3, &param))
		{
			if (PARAM_ONE(peb) == REG_CODE)
				param.one = process->reg[param.one - 1];
			if (PARAM_TWO(peb) == REG_CODE)
				param.two = process->reg[param.two - 1];
			process->reg[param.thr - 1] = \
			read_memory(process->pc + ((param.one + param.two) % IDX_MOD), env);
		}
	}
	process->pc += param_len(peb, 0, 3) + 2;
}
