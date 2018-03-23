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

static void			check_code(t_node *root, int fd)
{
	int				gnl;
	char			*line;
	t_node		*code;
	t_node		*new_code;

	line = NULL;
	code = create_node(CODE, NULL);
	add_child(root, code);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		check_line(code, line);
		ft_strdel(&line);
		new_code = create_node(CODE, NULL);
		add_child(code, new_code);
		code = new_code;
	}
	ft_printf("gnl = %d\n", gnl);
	if (gnl < 0)
		pexit("Erreur de read", -2);
	new_code = create_node(ENDCODE, NULL);
	add_child(code, new_code);
}

static void			check_header(t_node *root, int fd)
{
	int				gnl;
	char			*line;
	t_node			*header;

	line = NULL;
	header = create_node(HEADER, NULL);
	add_child(root, header);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (line && line[0] == '.')
			get_cmd(header, line, fd);
		ft_strdel(&line);
		if (header->children && header->children->next)
			break;
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
