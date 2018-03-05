/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:15:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
 /*
void print_label(t_env *env)
{
	t_label *tmp;
	t_roquet *tmp2;

	tmp = env->label;
	while(tmp)
	{
		tmp2 = tmp->appel;
		ft_printf("name = |%s|\n", tmp->name);
		ft_printf("index = %ld\n", tmp->index);
		while(tmp2)
		{
			ft_printf("pos = %ld\n", tmp2->pos);
			ft_printf("size_max = %ld\n", tmp2->size_max);
			ft_printf("[%d:%d]\n",tmp2->i, tmp2->j);
			tmp2 = tmp2->next;
		}
		ft_printf("\n\n");
		tmp = tmp->next;
	}
}*/

int get_label(char *name, t_env *env, int i, int size)
{
	t_label *tmp;
	char    tmp_char;

	while (name[i] && !(ft_isspace(name[i])) && name[i] != SEPARATOR_CHAR)
		i++;
	tmp_char = name[i];
	name[i] = '\0';
	tmp = env->label;
	while (tmp && tmp->next && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->name, name))
		if (tmp->index != -1)
			return (tmp->index - env->pos_last_inst);
	if (!(tmp && !ft_strcmp(tmp->name, name)))
	{
		if (tmp && (tmp->next = ft_memalloc_exit(sizeof(t_label))))
			tmp = tmp->next;
		else if ((env->label = ft_memalloc_exit(sizeof(t_label))))
			tmp = env->label;
		tmp->name = ft_strdup(name);
		tmp->index = -1;
	}
	name[i] = tmp_char;
	load_new_roquet(tmp, env, size);
	return (0);
}

void new_label(t_env *env, char *src, size_t end_src, t_label *tmp)
{
	char tmp_char;

	tmp_char = src[end_src];
	src[end_src] = '\0';
	if (tmp)
	{
		while(tmp->next && (ft_strncmp(src, tmp->name, end_src) || ft_strlen(tmp->name) != end_src))
			tmp = tmp->next;
		if (!ft_strncmp(src, tmp->name, end_src) && ft_strlen(tmp->name) == end_src)
			tmp->index = env->pos;
		else
		{
			tmp->next = ft_memalloc_exit(sizeof(t_label));
			tmp->next->name = ft_strdup(src);
			tmp = tmp->next;
		}
	}
	else
	{
		env->label = ft_memalloc_exit(sizeof(t_label));
		tmp = env->label;
		tmp->name = ft_strdup(src);
	}
	tmp->index = env->pos;
	src[end_src] = tmp_char;
}

int is_label(char *src, int start)
{
	while(src[start])
	{
		if (src[start] == LABEL_CHAR)
			return (1);
		else if (!ft_strchr(LABEL_CHARS, src[start]))
			return(0);
		if (ft_isspace(src[start]))
			return(0);
		++start;
	}
	return(0);
}

void check_label(t_env *env, t_label *tmp)
{
	t_roquet *tmp2;

	tmp = env->label;
	while(tmp && !env->error)
	{
		tmp2 = tmp->appel;
		if (tmp->index == -1)
		{
			env->line = tmp2->j;
			env->index = tmp2->i;
			ft_error(env, tmp->name, 9);
		}
		while(tmp2)
		{
			fill_memory(env->champ, tmp->index - tmp2->value,tmp2->size_max, tmp2->pos);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
