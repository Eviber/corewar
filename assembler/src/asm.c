/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 05:48:28 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/16 20:24:04 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*static t_rules	*get_rules(void)
{
	static t_rules	rules[] = {
	{ PROG, { HEADER, CODE, 0, 0 } },
	{ HEADER, { CMD_NAME, CMD_CMT, 0, 0 } },
	{ HEADER, { CMD_CMT, CMD_NAME, 0, 0 } },
	{ CODE, { LINE, CODE, 0, 0 } },
	{ CODE, { ENDCODE, 0, 0, 0 } },
	{ LINE, { LABEL, 0, 0, 0 } },
	{ LINE, { INST, 0, 0, 0 } },
	{ LINE, { LABEL, INST, 0, 0 } },
	{ PARAM, { PARAM, SEP, PARAM, 0 } },
	{ PARAM, { REG, 0, 0, 0 } },
	{ PARAM, { DIRECT, 0, 0, 0 } },
	{ PARAM, { IND, 0, 0, 0 } },
	{ 0, { 0, 0, 0, 0 } },
	};

	return (rules);
}*/

void				pexit(char *s, int i)
{
	perror(s);
	exit(i);
}

int					main(int argc, char **argv)
{
	t_node			*tree;
	int				fd;
	int				i;

	if (argc <= 1)
		ft_dprintf(2, "usage: ./asm <champion.s>\n");
	else
	{
		tree = NULL;
		i = 1;
		while (argv && argv[i])
		{
			fd = open(argv[i], O_RDONLY);
			if (fd == -1)
			{
				ft_printf("open error\n");
				pexit(argv[i], -1);
			}
			tree = lexer(argv[i], fd);
			if (!tree)
				pexit(argv[i], -1);
//			parser();
//			free_root(&root);
			close(fd);
			i++;
		}
	}
	return (0);
}
