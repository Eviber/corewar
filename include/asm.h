/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:11:14 by sbrochar          #+#    #+#             */
/*   Updated: 2018/03/13 17:01:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

typedef enum		e_token
{
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
	IND
}

typedef struct		s_node
{
	struct s_node	*parent;
	struct s_list	*children;
	t_token			type;
	char			*name;
}					t_node;

typedef struct		s_list
{
//	t_node			*start;
	t_node			*elem;
	t_node			*next;
}					t_list;

typedef struct		s_rules
{
	t_token			orig;
	t_token			*res;
}					t_rules;
