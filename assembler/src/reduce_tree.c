/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:39:28 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/23 10:39:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void erase_frontier_between_param(t_node *root, t_node *node_param)
{
  t_child *child;
  t_child *child_prev;

  if (root->type != INST)
  {
    child = root->children;
    while (child)
    {
      erase_frontier_between_param(child->elem, node_param);
      child = child->next;
    }
  }
  else if (!node_param)
    erase_frontier_between_param(root, root->children->next->elem);
  else if (root->children->next->elem->children->next)
  {
    child_prev = root->children;
    while (child_prev->next->elem->children->next)
    {
    child = root->children->next->elem->children->next;
    add_child(root, child->elem);
    del_child(root->children->next->elem, child); // tu leakserai pas toi ?

      child_prev = child_prev->next;
    }
  }
}

void erase_separator(t_node *root)
{
  t_child *child;

  if (root->type != PARAM)
  {
    child = root->children;
    while (child)
    {
      erase_separator(child->elem);
      child = child->next;
    }
  }
  else
  {
    child = root->children;
    if (child->elem->type == PARAM)
    {
      del_child(root, child->next);
      erase_separator(child->next->elem);
    }
  }
}

void reduce_param(t_node *root)
{
  t_node *tmp_tree;

  tmp_tree = root;
  erase_separator(tmp_tree);
  tmp_tree = root;
  print_tree(root);
  erase_frontier_between_param(tmp_tree, NULL);
}

 void reduce_tree(t_node *root)
 {
   t_node *tmp_tree;

   tmp_tree = root;
   reduce_param(tmp_tree);
   print_tree(root);
   //reduce_code(root);
 }
