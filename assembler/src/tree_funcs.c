/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:53:18 by sbrochar          #+#    #+#             */
/*   Updated: 2018/03/16 20:24:01 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

/*void				add_node(t_node *new, t_node *parent)
{
	if (new && parent)
	{
		new->parent = parent;
		add_child(parent, new);
	}
}*/

t_node				*create_node(t_token type, char *name)
{
	t_node			*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	if (node)
	{
		node->parent = NULL;
		node->children = NULL;
		node->type = type;
		if (name)
			node->name = ft_strdup(name);
		else
			node->name = NULL;
		return (node);
	}
	return (NULL);
}
