/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/02 15:53:16 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_ld_perm(void)
{
	char	**perm;

	if (!(perm = (char**)ft_memalloc(sizeof(char*) * 2)))
		ft_exit(strerror(errno));
	if (!(perm[0] = ft_strnew(2)))
		ft_exit(strerror(errno));
	if (!(perm[1] = ft_strnew(2)))
		ft_exit(strerror(errno));
	perm[0][0] = 0;
	perm[0][1] = 1;
	perm[0][2] = 1;
	perm[1][0] = 1;
	perm[1][1] = 0;
	perm[1][2] = 0;
	return (perm);
}

void			vm_ld(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	char			peb;

	peb = env->memory[process->pc + 1];
	if (!perm)
		perm = get_ld_perm();
	param.mod = L_DIR | IND_TARG | IMOD;
	if (!check_peb(peb, perm, 2))
	{
		process->carry = 0;
		get_param(&param, process, env);
		if ((env->verbose & SHOW_MOVE))
			show_pc_mov(process->pc, process->pc + param.len, param.len, env);
		if (!check_reg(peb, 2, &param))
			if (!(process->reg[param.two - 1] = param.one))
				process->carry = 1;
	}
	process->pc += param_len(peb, 1, 2) + 2;
}
