/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:52:56 by sbrochar          #+#    #+#             */
/*   Updated: 2018/03/22 14:36:15 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

static int line_not_empty(char *line)
{
	int i;

	i = -1;
	while (line && line[++i] && ft_isspace(line[i]) && line[i] != COMMENT_CHAR)
		;
	if (line[i] == COMMENT_CHAR)
		return(-1);
	return(i);
}

static void			check_code(t_node *root, int fd)
{
	int				gnl;
	int 			i;
	char			*line;
	t_node		*code;
	t_node		*new_code;
	t_node		*node_line;

	i = 0;
	line = NULL;
	code = create_node(CODE, NULL);
	add_child(root, code);
	while ((gnl = get_next_line(fd, &line)) > 0)
		if ((i = line_not_empty(line)) != -1 && (line[i] && line[i] != '#'))
		{
		  node_line = create_node(LINE, NULL);
		  add_child(code, node_line);
			check_line(node_line, line + i);
			ft_strdel(&line);
			new_code = create_node(CODE, NULL);
			add_child(code, new_code);
			code = new_code;
		}
	if (gnl < 0)
		pexit("Erreur de read", -2);
	add_child(code, create_node(ENDCODE, NULL));
}

static void			check_header(t_node *root, int fd)
{
	int				gnl;
	char			*line;
	t_node			*header;
	int i;

	line = NULL;
	i = 0;
	header = create_node(HEADER, NULL);
	add_child(root, header);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		while(line && line[i] && ft_isspace(line[i]) && line[i] != COMMENT_CHAR) // gerer ici si commentaire gerer ligne vide avev espace
			i++;
		if (line && line[i] != COMMENT_CHAR && line[i] == '.')
			get_cmd(header, line + i, fd);
		else if (line[i] != COMMENT_CHAR)
		{
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	if (gnl < 0)
		pexit("Erreur de read", -2);
}

t_node				*lexer(char *prog, int fd)
{
	t_node			*tree;

	tree = create_node(PROG, prog);
	if (tree)
	{
		check_header(tree, fd);
		check_code(tree, fd);
		print_tree(tree);
		return (tree);
	}
	return (NULL);
}
