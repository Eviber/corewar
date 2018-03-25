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

void 		del_child(t_node *parent, t_child *children)
{
	t_child 		*tmp_child;

	if (children == parent->children)
		parent->children = children->next;
	else
	{
		tmp_child = parent->children;
		while (tmp_child->next != children)
			tmp_child = tmp_child->next;
		tmp_child->next = children->next;
	}

	ft_memdel((void **)&children);
}

void 		add_next_child(t_node *parent, t_node *children)
{
	t_child 		*tmp_child;

	tmp_child = parent->children;
	while (tmp_child->next)
		tmp_child = tmp_child->next;
	tmp_child->next = (t_child *)ft_memalloc(sizeof(t_child));
	tmp_child->next->elem = children;
}

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
	pexit("Malloc returned null\n", 1);
	return (NULL);
}

void				add_child(t_node *parent, t_node *children)
{
	t_child			*child;

	if (parent->children)
		add_next_child(parent, children);
	else
	{
		child = (t_child *)ft_memalloc(sizeof(t_child));
		if (child)
		{
			parent->children = child;
			child->elem = children;
			child->next = NULL;
		}
		else
			pexit("Malloc returned null\n", 1);
	}
}
