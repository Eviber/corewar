/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:11:14 by sbrochar          #+#    #+#             */
/*   Updated: 2018/03/16 20:24:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef enum		e_token
{
	NONE,
	PROG,
	HEADER,
	CODE,
	LINE,
	INST,
	PARAM,
	CMD_NAME,
	CMD_CMT,
	LABEL,
	FCT,
	SEP,
	REG,
	DIRECT,
	IND,
	ENDCODE
}					t_token;

typedef struct		s_node
{
	struct s_node	*parent;
	struct s_child	*children;
	t_token			type;
	char			*name;
}					t_node;

typedef struct		s_child
{
//	t_node			*start;
	t_node			*elem;
	t_node			*next;
}					t_child;

typedef struct		s_rules
{
	t_token			orig;
	t_token			res[4];
}					t_rules;

t_node				*lexer(char *prog, int fd);

t_node				*create_node(t_token type, char *name);

void				pexit(char *s, int i);

#endif
