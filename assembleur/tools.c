/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/24 14:57:25 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_int_param(char *str, t_env *env, long i)
{
	while (str[++i] && str[i] != SEPARATOR_CHAR && str[i] != COMMENT_CHAR &&
			!ft_isspace(str[i]) && !env->error && str[i] != OTHER_COMMENT_CHAR)
		if (!ft_isdigit(str[i]) || str[i] == '-')
			ft_error(env, str, 4);
	return (1);
}

void	load_new_roquet(t_label *target, t_env *env, int size)
{
	t_roquet *tmp;
	t_roquet *new_roquet;

	tmp = target->appel;
	new_roquet = ft_memalloc_exit(sizeof(t_roquet));
	new_roquet->value = env->pos_last_inst;
	new_roquet->pos = env->pos;
	new_roquet->i = env->index;
	new_roquet->j = env->line;
	new_roquet->size_max = size;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new_roquet;
	else
		target->appel = new_roquet;
}

void	fill_memory(char *mem, long value, int size, int start)
{
	while (value && size--)
	{
		mem[start + size] = (char)value % 256;
		value = (value - (value % 256)) / 256;
	}
}

void	*ft_memalloc_exit(size_t size)
{
	void *mem;

	if (!(mem = ft_memalloc(size)))
	{
		ft_dprintf(2, "Malloc has failed in this execution\n");
		exit(1);
	}
	return (mem);
}

void	memory_manager(t_env *env, int size)
{
	char *save;
	long cmp;

	if (env->pos + size > CHAMP_MAX_SIZE)
		env->error = 2;
	else if (env->pos + size > env->size_champ)
	{
		cmp = -1;
		save = env->champ;
		env->champ = ft_memalloc_exit(env->pos + 40);
		while (++cmp < env->size_champ)
			env->champ[cmp] = save[cmp];
		ft_memdel((void**)&save);
		env->size_champ = env->pos + 40;
	}
}
