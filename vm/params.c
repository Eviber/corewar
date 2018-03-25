/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:03:33 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/23 15:57:26 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				check_peb(unsigned char peb, char **perm, int nb_param)
{
	int		param;
	int		len;
	char	current;

	param = -1;
	len = 0;
	while (++param < nb_param)
	{
		current = (peb >> (8 - ((param + 1) * 2))) & IND_CODE;
		if (!(current > 0 && perm[param][current - 1]))
			return (1);
	}
	return (0);
}

int				get_param_value(unsigned int at, int len, int *ret, t_vm *env)
{
	int		i;

	i = -1;
	*ret = 0;
	while (++i < len)
		*ret = ((*ret) << 8) + env->memory[(at + i) % MEM_SIZE];
	if (len == 2)
		*ret = (int)(short)*ret;
	return (len);
}

static void		load_param(t_param *param, t_process *process, t_vm *env)
{
	int				pc;
	unsigned char	peb;

	pc = process->pc + 2;
	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	if ((PARAM_ONE(peb)) == REG_CODE)
		pc += get_param_value(pc, 1, &param->one, env);
	else if ((PARAM_ONE(peb)) == IND_CODE || !(param->mod & L_DIR))
		pc += get_param_value(pc, 2, &param->one, env);
	else if (PARAM_ONE(peb))
		pc += get_param_value(pc, 4, &param->one, env);
	if ((PARAM_TWO(peb)) == REG_CODE)
		pc += get_param_value(pc, 1, &param->two, env);
	else if ((PARAM_TWO(peb)) == IND_CODE || !(param->mod & L_DIR))
		pc += get_param_value(pc, 2, &param->two, env);
	else if (PARAM_TWO(peb))
		pc += get_param_value(pc, 4, &param->two, env);
	if ((PARAM_THR(peb)) == REG_CODE)
		pc += get_param_value(pc, 1, &param->thr, env);
	else if ((PARAM_THR(peb)) == IND_CODE || !(param->mod & L_DIR))
		pc += get_param_value(pc, 2, &param->thr, env);
	else if (PARAM_THR(peb))
		pc += get_param_value(pc, 4, &param->thr, env);
}

void			get_param(t_param *param, t_process *process, t_vm *env)
{
	unsigned char	peb;

	peb = env->memory[(process->pc + 1) % MEM_SIZE];
	load_param(param, process, env);
	if ((param->mod & IND_TARG))
	{
		if ((PARAM_ONE(peb)) == IND_CODE && (param->mod & IMOD))
			param->one = \
			read_memory(process->pc + ((int)(short)param->one % IDX_MOD), env);
		else if ((PARAM_ONE(peb)) == IND_CODE)
			param->one = read_memory(process->pc + (int)(short)param->one, env);
		if ((PARAM_TWO(peb)) == IND_CODE && (param->mod & IMOD))
			param->two = \
			read_memory(process->pc + ((int)(short)param->two % IDX_MOD), env);
		else if ((PARAM_TWO(peb)) == IND_CODE)
			param->two = read_memory(process->pc + (int)(short)param->two, env);
		if ((PARAM_THR(peb)) == IND_CODE && (param->mod & IMOD))
			param->thr = \
			read_memory(process->pc + ((int)(short)param->thr % IDX_MOD), env);
		else if ((PARAM_THR(peb)) == IND_CODE)
			param->thr = read_memory(process->pc + (int)(short)param->thr, env);
	}
}

int				param_len(unsigned char peb, int mod, int nb_param)
{
	int		param;
	int		len;
	char	current;

	param = -1;
	len = 0;
	while (++param < nb_param)
	{
		current = (peb >> (8 - ((param + 1) * 2))) & IND_CODE;
		if (current == REG_CODE)
			len += 1;
		else if (current == DIR_CODE && mod == 1)
			len += 4;
		else if (current)
			len += 2;
	}
	return (len);
}
