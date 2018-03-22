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

static void			get_cmd(char *line)
{
	int				i;
	char			*cmd;
	t_node			*header;

	i = 1;
	header = create_node(HEADER, NULL);
	while (line[i] != ' ' && line[i] != '\t')
		i++;
	cmd = ft_strsub(line, 1, i - 1);
	if (!cmd)
		pexit(NULL, -1);
	if (!ft_strcmp(cmd, "name")) { }
//		register_name_command();
	else if (!ft_strcmp(cmd, "comment")) { }
//		register_comment_command();
	ft_strdel(&cmd);
}

static void			check_header(/*t_node *root,*/ int fd)
{
	int				gnl;
	char			*line;

	line = NULL;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (line && !line[0])
		{
			ft_strdel(&line);
			continue ;
		}
		if (line && line[0] == '.')
			get_cmd(line);
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
		check_header(/*tree,*/ fd);
//		check_code(tree);
		return (tree);
	}
	return (NULL);
}
