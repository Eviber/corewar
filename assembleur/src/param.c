/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:15:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op *get_opt()
{
	static t_op    op_tab[17] = {
		{"live", 1, T_DIR , 0, 0, 1},
		{"ld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 2},
		{"st", 2, T_REG + (T_IND + T_REG) * 8, 1, 0, 3},
		{"add", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 4},
		{"sub", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 5},
		{"and", 3, T_REG + T_DIR + T_IND + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 6},
		{"or", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 7},
		{"xor", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 8},
		{"zjmp", 1, T_DIR, 0, 1, 9},
		{"ldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1, 10},
		{"sti", 3, T_REG + (T_REG + T_DIR + T_IND) * 8 + (T_DIR + T_REG) * 64, 1, 1, 11},
		{"fork", 1, T_DIR, 0, 1, 12},
		{"lld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 13},
		{"lldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1, 14},
		{"lfork", 1, T_DIR, 0, 1, 15},
		{"aff", 1, T_REG, 1, 0, 16},
		{0, 0, 0, 0, 0, 15} };

	return(op_tab);
}

static int check_int_param(char *str, t_env *env, long i)
{
	while(str[++i] && str[i]!= SEPARATOR_CHAR &&
    !ft_isspace(str[i]) && !env->error)
		if (!ft_isdigit(str[i]) || str[i] == '-')
			ft_error(env, str, 4);
	return(1);
}

static int check_param(char *src, t_env *env, t_op op, short type)
{
	int size;
	unsigned int value;
	int cmp;
	char current_type;

	src = src + env->index;
	if (*src == 'r' && (type & T_REG && (current_type = 1)))
		size = 1;
	else if ((*src == LABEL_CHAR || ft_isdigit(*src) || *src == '-') && (type & T_IND) && (current_type = 3))
		size = 2;
	else if (*src == DIRECT_CHAR && (type & T_DIR) && (current_type = 2))
		size = 4 / ((op.half_dir_size) ? 2 : 1);
	else if (!(size = 0))
		ft_error(env, src, 4);
	if (!(value = 0) && (*src == LABEL_CHAR || (src[1] == LABEL_CHAR && ++src)))
		value = get_label(++src, env, 0, size);
	else if (check_int_param(src , env, !ft_isdigit(*src)))
		value = ft_atoi((!ft_isdigit(*src) && (*src != '-')) ? ++src : src);
	if ((cmp = size) && size == 1 && value > REG_NUMBER)
		ft_error(env, src, 5);
	memory_manager(env, cmp);
	fill_memory(env->champ, value, cmp, env->pos);
	env->pos += size;
	return (current_type);
}


void get_param(t_op op, char *src, t_env *env)
{
	int state;
	int nb_arg;
	short type;
	int pos;
	unsigned char octal;

	state = 0;
	nb_arg = 1;
	pos = 0;
	type = op.type;
	memory_manager(env, 1);
	env->champ[env->pos++] = op.opcode;
	if (op.has_octal)
		pos = env->pos++;
	while(src[env->index] && src[env->index] != COMMENT_CHAR && !env->error)
	{
		if (ft_isspace(src[env->index]))
      ;
    else if (state == 0 && src[env->index] != SEPARATOR_CHAR && (state = 1))
			octal = octal * 4 + check_param(src, env, op, type);
		else if ((state == 1 || state == 3) && src[env->index] == SEPARATOR_CHAR)
		{
			if (++nb_arg > op.nb_params)
				ft_error(env, op.name, 6);
			state = 0;
			type /= 8;
		}
		else if (state != 1)
			ft_error(env, op.name, 4);
		++env->index;
	}
	if (pos)
	{
		while(octal < 64)
			octal *= 4;
		memory_manager(env, 1);
		env->champ[pos] = octal;
		}
}
