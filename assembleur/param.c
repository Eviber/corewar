/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/04/05 16:55:23 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op			*get_opt(t_op *op_tab)
{
	op_tab = ft_memalloc_exit(sizeof(t_op) * 17);
	op_tab[0] = (t_op){"live", 1, T_DIR, 0, 0, 1};
	op_tab[1] = (t_op){"ld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 2};
	op_tab[2] = (t_op){"st", 2, T_REG + (T_IND + T_REG) * 8, 1, 0, 3};
	op_tab[3] = (t_op){"add", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 4};
	op_tab[4] = (t_op){"sub", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 5};
	op_tab[5] = (t_op){"and", 3, T_REG + T_DIR + T_IND + (T_REG + T_IND + T_DIR)
		* 8 + T_REG * 64, 1, 0, 6};
	op_tab[6] = (t_op){"or", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR)
		* 8 + T_REG * 64, 1, 0, 7};
	op_tab[7] = (t_op){"xor", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR)
		* 8 + T_REG * 64, 1, 0, 8};
	op_tab[8] = (t_op){"zjmp", 1, T_DIR, 0, 1, 9};
	op_tab[9] = (t_op){"ldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG)
		* 8 + T_REG * 64, 1, 1, 10};
	op_tab[10] = (t_op){"sti", 3, T_REG + (T_REG + T_DIR + T_IND) * 8 +
	(T_DIR + T_REG) * 64, 1, 1, 11};
	op_tab[11] = (t_op){"fork", 1, T_DIR, 0, 1, 12};
	op_tab[12] = (t_op){"lld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 13};
	op_tab[13] = (t_op){"lldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG)
		* 8 + T_REG * 64, 1, 1, 14};
	op_tab[14] = (t_op){"lfork", 1, T_DIR, 0, 1, 15};
	op_tab[15] = (t_op){"aff", 1, T_REG, 1, 0, 16};
	return (op_tab);
}

static int		check_param(char *src, t_env *env, t_op op, short type)
{
	unsigned int	value;
	char			current_type;
	int				size;
	int				cmp;

	src = src + env->index;
	if (*src == 'r' && (type & T_REG && (current_type = 1)))
		size = 1;
	else if ((*src == LABEL_CHAR || ft_isdigit(*src) ||
				*src == '-') && (type & T_IND) && (current_type = 3))
		size = 2;
	else if (*src == DIRECT_CHAR && (type & T_DIR) && (current_type = 2))
		size = 4 / ((op.half_dir_size) ? 2 : 1);
	else if (!(size = 0))
		ft_error(env, src, 4);
	if (!(value = 0) && (*src == LABEL_CHAR || (src[1] == LABEL_CHAR && ++src)))
		value = get_label(++src, env, 0, size);
	else if (check_int_param(src, env, !ft_isdigit(*src)))
		value = ft_atoi((!ft_isdigit(*src) && (*src != '-')) ? ++src : src);
	if ((cmp = size) && size == 1 && value > REG_NUMBER)
		ft_error(env, src, 5);
	memory_manager(env, cmp);
	fill_memory(env->champ, value, cmp, env->pos);
	env->pos += size;
	return (current_type);
}

unsigned char	check_norme(int nb_arg, t_op op, t_env *env,
		unsigned char octal)
{
	if (!env->error && nb_arg < op.nb_params)
		ft_error(env, op.name, 15);
	return (octal);
}

unsigned char	launc_param(t_op op, char *src, t_env *env, unsigned char octal)
{
	int				stat;
	int				nb_arg;
	short			type;

	stat = 0;
	nb_arg = 1;
	type = op.type;
	ft_printf("src = %s\n", src);
	while (src[env->index] && src[env->index] != COMMENT_CHAR
			&& !env->error && src[env->index] != OTHER_COMMENT_CHAR)
	{
		ft_printf("stav = %d src[%d] = %c\n", stat, env->index, src[env->index]);
		if (ft_isspace(src[env->index]))
			stat = (stat = 1) ? 2 : stat;
		else if (stat == 0 && src[env->index] != SEPARATOR_CHAR && (stat = 1))
			octal = octal * 4 + check_param(src, env, op, type);
		else if ((stat == 1 || stat == 3) && src[env->index] == SEPARATOR_CHAR)
		{
			if (!(stat = 0) && ++nb_arg > op.nb_params)
				ft_error(env, op.name, 6);
			type /= 8;
		}
		else if ((stat != 1 && stat != 2) || (stat == 2 && src[env->index] != ft_isspace(src[env->index])))
			ft_error(env, op.name, 4);
		++env->index;
	}
	return (check_norme(nb_arg, op, env, octal));
}

void			get_param(t_op op, char *src, t_env *env)
{
	unsigned char	octal;
	int				pos;

	pos = 0;
	memory_manager(env, 1);
	env->champ[env->pos++] = op.opcode;
	if (op.has_octal)
		pos = env->pos++;
	octal = launc_param(op, src, env, 0);
	if (!env->error)
	{
		if (pos)
		{
			while (octal < 64)
				octal *= 4;
			memory_manager(env, 1);
			env->champ[pos] = octal;
		}
		if (!src[env->index])
			--env->index;
	}
}
