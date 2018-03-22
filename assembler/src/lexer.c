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

static void			check_header(t_node *root, int fd)
{
	int				gnl;
	char			*line;
	t_node			*header;

	line = NULL;
	header = create_node(HEADER, NULL);

	create_child(root, header);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (line && line[0] == '.')
			get_cmd(header, line, fd);
		ft_strdel(&line);
	}
/*	if (gnl == -1)
	{
		ft_printf("gnl error\n");
		perror(prog);
	}*/
}

t_node				*lexer(char *prog, int fd)
{
	t_node			*tree;

	tree = create_node(PROG, prog);
	if (tree)
	{
		check_header(tree, fd);
		check_code(tree);
		print_tree(tree);
		return (tree);
	}
	return (NULL);
}
