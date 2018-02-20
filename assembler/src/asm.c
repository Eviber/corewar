/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 05:48:28 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/16 05:48:45 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static t_elem		init_tree(void)
{
	t_elem		ret;

	ret.name = NULL;
	ret.type = 0;
	ret.pos = -1;
	ret.children = NULL;
	ret.next = NULL;
	return (ret);
}

static void		free_elem(t_elem *elem)
{
	int		i;

	i = 0;
	if (elem)
	{
		if (elem->name)
			ft_strdel(&(elem->name));
		if (elem->children)
		{
			while ((elem->children)[i])
			{
				free_elem((elem->children)[i]);
				i++;
			}
		}
	}
}

static void		free_tree(t_elem *tree)
{
	int		i;

	i = 0;
	while (tree->next)
	{
		while ((tree->children)[i])
		{
			free_elem((tree->children)[i]);
			i++;
		}
		tree = tree->next;
	}
}

int			main(int argc, char **argv)
{
	t_elem		tree;

	tree = init_tree();
	if (argc <= 1)
		ft_putendl("usage: ./asm champion.s");
	else
	{
		argv++;
		while (argv && *argv)
		{
			lexer(&tree, *argv);
			//verif(tree);
			//if (tree)
			//	parser(&tree);
			argv++;
		}
	}
	free_tree(&tree);
	return (0);
}
