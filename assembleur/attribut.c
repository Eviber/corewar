/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/24 17:15:46 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** state binaire = etat de la recherche de attr
** 0b00000000 = nothing find
** 0b00xxx001 = .name find
** 0b00xxx011 = char *name find
** 0b00xxx111 = char *name finish
** 0b00001xxx = .comment find
** 0b00011xxx = char *comment find
** 0b00111xxx = char *comment finish
** 0b00111111 = attribut finis;
*/

int		ft_fill_attr(char *line, t_env *env, char state, int effective_pos)
{
	while (line[++env->index] && line[env->index] != COMMENT_CHAR
			&& !env->error && line[env->index] != OTHER_COMMENT_CHAR)
	{
		if (line[env->index] == '"' && !(state & 4) && state & 1)
		{
			if (state & 2 && !effective_pos)
				ft_error(env, NULL, 11);
			state |= ((state & 2) ? 4 : 2);
		}
		else if (line[env->index] == '"' && !(state & 32) && state & 8)
		{
			if (state & 16 && !effective_pos)
				ft_error(env, NULL, 12);
			state |= ((state & 16) ? 32 : 16);
		}
		else if ((state & 2 && !(state & 4)) && env->pos -
				sizeof(COREWAR_EXEC_MAGIC) > PROG_NAME_LENGTH)
			ft_error(env, NULL, 2);
		else if ((state & 16 && !(state & 32)) && env->pos -
				sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH +
				sizeof(long) > COMMENT_LENGTH)
			ft_error(env, NULL, 3);
		else if (!ft_isspace(line[env->index]) && (((state & 2) && (state & 4))
					|| (!(state & 2) && !(state & 4))) && (((state & 32) &&
						(state & 16)) || ((state & 32) && (state & 16))))
			ft_error(env, NULL, 1);
		else if (((state & 2) && !(state & 4)) ||
				((state & 16) && !(state & 32)))
			env->res[++effective_pos + env->pos] = line[env->index];
	}
	if (((state & 2) && !(state & 4)) || ((state & 16) && !(state & 32)))
		env->res[++effective_pos + env->pos] = '\n';
	env->pos += effective_pos;
	return (state);
}

char	search_attr(char *line, t_env *env, char state)
{
	while (line[++env->index] && line[env->index] != COMMENT_CHAR &&
			line[env->index] != OTHER_COMMENT_CHAR && !env->error)
	{
		if (ft_isspace(env->index))
			;
		else if (!ft_strncmp(line + env->index, NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)) && !(state & 1))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC);
			env->index += ft_strlen(NAME_CMD_STRING) - 1;
			return (state | 1);
		}
		else if (!ft_strncmp(line + env->index, COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)) && !(state & 8))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC) +
				PROG_NAME_LENGTH + sizeof(long);
			env->index += ft_strlen(COMMENT_CMD_STRING) - 1;
			return (state | 8);
		}
		else
			ft_error(env, NULL, 10);
	}
	return (state);
}

void	read_attribut(t_env *env, char *line)
{
	static char state = 0;

	if (env->state == 0 && (env->state = 1))
		state = 0;
	if ((!(state & 2) || (state & 2 && state & 4 && !(state & 8)))
			&& ((!(state & 16)) || (state & 16 && state & 32 && !(state & 2))))
		state = search_attr(line, env, state);
	if (((state & 1) && !(state & 4)) || ((state & 8) && !(state & 32)))
		state = ft_fill_attr(line, env, state, 0);
	if (state == 63)
		env->state = 2;
}
