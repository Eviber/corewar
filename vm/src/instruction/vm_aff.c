/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/03 19:35:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_aff_perm(void)
{
	char	**perm;

	if (!(perm = (char**)ft_memalloc(sizeof(char*) * 1)))
		ft_exit(strerror(errno));
	if (!(perm[0] = ft_strnew(2)))
		ft_exit(strerror(errno));
	perm[0][0] = 1;
	perm[0][1] = 0;
	perm[0][2] = 0;
	return (perm);
}

void			vm_aff(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	char			peb;

	peb = env->memory[process->pc + 1];
	if (!perm)
		perm = get_aff_perm();
	param.mod = 0;
	if (!check_peb(peb, perm, 1))
	{
		get_param(&param, process, env);
		if ((env->verbose & SHOW_MOVE))
			show_pc_mov(process->pc, process->pc + param.len, param.len, env);
		if (!check_reg(peb, 1, &param))
			ft_putchar((unsigned char)process->reg[param.one - 1]);
	}
	process->pc += param_len(peb, 1, 1) + 2;
}
