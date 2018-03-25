/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/23 14:54:53 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_st_perm(void)
{
	char	**perm;

	if (!(perm = (char**)ft_memalloc(sizeof(char*) * 2)))
		ft_exit(strerror(errno));
	if (!(perm[0] = ft_strnew(2)))
		ft_exit(strerror(errno));
	if (!(perm[1] = ft_strnew(2)))
		ft_exit(strerror(errno));
	perm[0][0] = 1;
	perm[0][1] = 0;
	perm[0][2] = 0;
	perm[1][0] = 1;
	perm[1][1] = 0;
	perm[1][2] = 1;
	return (perm);
}

void			vm_st(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	char			peb;

	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	if (!perm)
		perm = get_st_perm();
	param.mod = IMOD;
	param.len = param_len(peb, 1, 2) + 2;
	if (!check_peb(peb, perm, 2))
	{
		get_param(&param, process, env);
		if (!check_reg(peb, 2, &param))
		{
			if (PARAM_TWO(peb) == REG_CODE)
				process->reg[param.two - 1] = process->reg[param.one - 1];
			else
				write_memory(process->reg[param.one - 1], process->pc + \
				(((int)(short)param.two) % IDX_MOD), env, process->champ);
		}
	}
	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + param.len, param.len, env);
	process->pc += param.len;
}
