/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/04/05 16:33:04 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_label(char *name, t_env *env, int i, int size)
{
	t_label *tmp;

	while (name[i] && !(ft_isspace(name[i])) && name[i] != SEPARATOR_CHAR)
		i++;
	tmp = env->label;
	while (tmp && tmp->next && (ft_strncmp(tmp->name, name, i) || tmp->name[i]))
		tmp = tmp->next;
	if (tmp && !ft_strncmp(tmp->name, name, i) && !(tmp->name[i]))
		if (tmp->index != -1)
			return (tmp->index - env->pos_last_inst);
	if (!tmp || (ft_strncmp(tmp->name, name, i) || tmp->name[i]))
	{
		if (tmp && (tmp->next = ft_memalloc_exit(sizeof(t_label))))
			tmp = tmp->next;
		else if ((env->label = ft_memalloc_exit(sizeof(t_label))))
			tmp = env->label;
		tmp->name = ft_strsub(name, 0, i);
		tmp->index = -1;
	}
	load_new_roquet(tmp, env, size);
	return (0);
}

void	new_label(t_env *env, char *src, size_t end_src, t_label *tmp)
{
	if (tmp)
	{
		while (tmp->next && (ft_strncmp(src, tmp->name, end_src) ||
					tmp->name[end_src]))
			tmp = tmp->next;
		if (tmp && !ft_strncmp(src, tmp->name, end_src) && !tmp->name[end_src])
			tmp->index = env->pos;
		else if ((tmp->next = ft_memalloc_exit(sizeof(t_label))))
		{
			tmp->next->name = ft_strsub(src, 0, end_src);
			tmp = tmp->next;
		}
	}
	else
	{
		env->label = ft_memalloc_exit(sizeof(t_label));
		tmp = env->label;
		tmp->name = ft_strsub(src, 0, end_src);
	}
	tmp->index = env->pos;
}

int		is_label(char *src, int start)
{
	while (src[start])
	{
		if (src[start] == LABEL_CHAR)
			return (1);
		else if (!ft_strchr(LABEL_CHARS, src[start]))
			return (0);
		if (ft_isspace(src[start]))
			return (0);
		++start;
	}
	return (0);
}

void	check_label(t_env *env, t_label *tmp)
{
	t_roquet *tmp2;

	tmp = env->label;
	while (tmp && !env->error)
	{
		tmp2 = tmp->appel;
		if (tmp->index == -1)
		{
			env->line = tmp2->j;
			env->index = tmp2->i;
			ft_error(env, tmp->name, 9);
		}
		while (tmp2)
		{
			fill_memory(env->champ, tmp->index - tmp2->value,
					tmp2->size_max, tmp2->pos);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	clean_label(t_env *env, t_label *tmp)
{
	t_roquet *tmp2;

	tmp2 = NULL;
	while (tmp)
	{
		tmp = env->label->next;
		tmp2 = env->label->appel;
		while (tmp2)
		{
			tmp2 = env->label->appel->next;
			ft_memdel((void **)&env->label->appel);
			env->label->appel = tmp2;
		}
		ft_strdel(&env->label->name);
		ft_memdel((void **)&env->label);
		env->label = tmp;
	}
}
