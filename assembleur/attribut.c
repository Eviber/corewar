/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/27 21:25:47 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_fill_attr(char *line, t_env *env, char *mem, int effective_pos)
{
	while (line[++env->index] && !env->error && ((*mem % 2) == 0 || (line[
		env->index] != COMMENT_CHAR && line[env->index] != OTHER_COMMENT_CHAR)))
	{
		if (line[env->index] == '"')
		{
			if (effective_pos == 0 && (*mem % 2) == 0)
				ft_error(env, NULL, 11 + (*mem > 4));
			(*mem)++;
		}
		else if (*mem < 4 && env->pos + effective_pos -
				sizeof(COREWAR_EXEC_MAGIC) >= PROG_NAME_LENGTH)
			ft_error(env, NULL, 2);
		else if (*mem > 4 && env->pos + effective_pos -
				(sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH +
				sizeof(long)) >= COMMENT_LENGTH)
			ft_error(env, NULL, 3);
		else if (!ft_isspace(line[env->index]) && (*mem % 2) == 1)
			ft_error(env, NULL, 1);
		else if ((*mem % 2) == 0)
			env->res[effective_pos++ + env->pos] = line[env->index];
	}
	if ((*mem % 2) == 0)
		env->res[effective_pos++ + env->pos] = '\n';
	env->pos += effective_pos;
}

void	search_attr(char *line, t_env *env, char *name, char *comment)
{
	while (line[++env->index] && line[env->index] != COMMENT_CHAR &&
			line[env->index] != OTHER_COMMENT_CHAR && !env->error)
	{
		if (ft_isspace(line[env->index]))
			;
		else if (!ft_strncmp(line + env->index, NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)) && !*name && (*name = 1))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC);
			env->index += ft_strlen(NAME_CMD_STRING) - 1;
			return ;
		}
		else if (!ft_strncmp(line + env->index, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)) && !*comment && (*comment = 5))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC) +
				PROG_NAME_LENGTH + sizeof(long);
			env->index += ft_strlen(COMMENT_CMD_STRING) - 1;
			return ;
		}
		else
			ft_error(env, NULL, 10);
	}
}

void	read_attribut(t_env *env, char *line)
{
	static char name;
	static char comment;

	if (env->state == 0 && (env->state = 1))
	{
		name = 0;
		comment = 0;
	}
	if ((name == 0 && comment == 7) || (name == 3 && comment == 0) ||
			(name == 0 && comment == 0))
		search_attr(line, env, &name, &comment);
	if ((name > 0 && name < 3) || (comment > 4 && comment < 7))
		ft_fill_attr(line, env, (name && name != 3) ? &name : &comment, 0);
	if (name == 3 && comment == 7)
		env->state = 2;
}
