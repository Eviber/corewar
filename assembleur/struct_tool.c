/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/27 21:26:12 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	switch_extension(t_env *env, char *src, char *new_extension)
{
	char	*res;
	size_t	cmp;
	size_t	i;

	cmp = ft_strlen(src);
	i = cmp;
	while (i-- && src[i] != '.')
		;
	if (src[i] != '.')
		ft_error(env, src, 14);
	else
	{
		res = ft_memalloc_exit(i + ft_strlen(new_extension) + 1);
		cmp = cmp - (cmp - i);
		i = -1;
		while (++i < cmp)
			res[i] = src[i];
		cmp = -1;
		while (new_extension[++cmp])
			res[i++] = new_extension[cmp];
		env->name = res;
	}
}

void	fill_length_file(t_env *env)
{
	long tmp;

	tmp = env->pos;
	if (tmp > CHAMP_MAX_SIZE)
		ft_error(env, NULL, 8);
	fill_memory(env->res, tmp, sizeof(long),
			sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH);
}

int		find_next(char *src, char car)
{
	int i;

	i = -1;
	while (src[++i] && src[i] != car)
		;
	if (src[i] == car)
		return (i);
	else
		return (0);
}

int		find_next_instruction(char *src)
{
	int i;

	i = -1;
	while (src[++i] && src[i] != LABEL_CHAR && src[i] !=
			DIRECT_CHAR && src[i] != COMMENT_CHAR && !ft_isspace(src[i])
			&& src[i] != OTHER_COMMENT_CHAR)
		;
	if (src[i])
		return (i);
	else
		return (i);
}

void	check_error(t_env *env)
{
	if (!env->error)
	{
		if (env->state != 3)
			ft_error(env, NULL, 10);
		else if (env->pos == 0 && ((env->error = 1)))
			ft_error(env, NULL, 13);
	}
}
