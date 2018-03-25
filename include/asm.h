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
# include <corewar.h>

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
	t_node			*elem;
	struct s_child			*next;
}					t_child;

typedef struct		s_rules
{
	int 				possibility;
	t_token			res[5];
}					t_rules;

t_node				*lexer(char *prog, int fd);

t_node				*create_node(t_token type, char *name);
void				add_child(t_node *parent, t_node *children);
void 		del_child(t_node *parent, t_child *children);

void				pexit(char *s, int i);

void			get_cmd(t_node *header,char *line, int fd);

void	print_tree(t_node *tree);
void print_token(int index, int deepness);

void check_line(t_node *node_line, char *line);
void check_param(t_node *node_param, char *param, int i);

void parser(t_node *root);

 void reduce_tree(t_node *root);

#endif
