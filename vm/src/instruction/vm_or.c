/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/24 16:30:14 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		**get_or_perm(void)
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

void			vm_or(t_process *process, t_vm *env)
{
	static char		**perm = NULL;
	t_param			param;
	int				result;

	if (!perm)
		perm = get_or_perm();
	param.mod = L_DIR | IND_TARG;
	process->carry = 0;
	if (!check_peb(env->memory[process->pc + 1], perm, 3))
	{
		get_param(&param, process, env);
		if (!check_reg(env->memory[process->pc + 1], &param))
		{
			if ((PARAM_ONE(env->memory[process->pc + 1])) == REG_CODE)
				param.one = process->reg[param.one - 1];
			if ((PARAM_TWO(env->memory[process->pc + 1])) == REG_CODE)
				param.two = process->reg[param.two - 1];
			result = param.one | param.two;
			if (!result)
				process->carry = 1;
			process->reg[param.thr - 1] = (unsigned int)result;
		}
	}
	process->pc += param_len(env->memory[process->pc + 1], 1, 3) + 2;
}
