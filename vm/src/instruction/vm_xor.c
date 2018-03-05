/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/05 15:07:44 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_xor_perm(void)
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
	perm[1][2] = 1;
	perm[2][0] = 1;
	perm[2][1] = 0;
	perm[2][2] = 0;
	return (perm);
}

void			vm_xor(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	char			peb;

	peb = env->memory[process->pc + 1];
	if (!perm)
		perm = get_xor_perm();
	param.mod = L_DIR | IND_TARG;
	param.len = param_len(peb, 1, 3) + 2;
	if (!check_peb(peb, perm, 3))
	{
		get_param(&param, process, env);
		if (!check_reg(peb, 3, &param))
		{
			if (PARAM_ONE(peb) == REG_CODE)
				param.one = process->reg[param.one - 1];
			if (PARAM_TWO(peb) == REG_CODE)
				param.two = process->reg[param.two - 1];
			process->carry = \
			!(process->reg[param.thr - 1] = param.one ^ param.two) ? 1 : 0;
		}
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + param.len, param.len, env);
	process->pc += param.len;
}
