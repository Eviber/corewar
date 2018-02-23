/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:33:32 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 21:26:30 by vsporer          ###   ########.fr       */
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
	unsigned int	p_one;
	unsigned int	p_two;

	if (!perm)
		perm = get_st_perm();
	if (!check_peb(env->memory[process->pc + 1], perm, 2))
	{
	ft_putendl("###############");
		p_one = get_param_value(process->pc + 2, 1, env);
		if ((PARAM_TWO(env->memory[process->pc + 1])) == REG_CODE)
		{
			p_two = get_param_value(process->pc + 3, 1, env);
			if (p_two <= 16 && p_two > 0 && p_one <= 16 && p_one > 0)
				process->reg[p_two - 1] = process->reg[p_one - 1];
		}
		else
		{
			p_two = get_param_value(process->pc + 3, 2, env);
			if (p_one <= 16 && p_one > 0)
				write_memory(process->reg[p_one - 1], \
				process->pc + (p_two % IDX_MOD), env);
		}
	}
	process->pc += param_len(env->memory[process->pc + 1], 0, 2) + 2;
}
