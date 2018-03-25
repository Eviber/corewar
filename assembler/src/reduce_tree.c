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

void erase_frontier_between_param(t_node *root)
{
  t_child *child;
  t_child *prev_child;

  if (root->type != INST)
  {
    child = root->children;
    while (child)
    {
      erase_frontier_between_param(child->elem);
      child = child->next;
    }
  }
  else
  {
    child = root->children->next;
    prev_child = root;
    while (child->elem->type == PARAM)
    {
      if (child != prev_child->elem->children->next->elem->children->next)
        prev_child = child;
      if (child->elem->children->next)
        child = child->elem->children->next;
      else
      {
        while (prev_child->next)
          prev_child =  prev_child->next;
        prev_child->next = child;
        del_child(prev_child->elem,
        break;
      }
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
  erase_frontier_between_param(tmp_tree);
}

 void reduce_tree(t_node *root)
 {
   t_node *tmp_tree;

   tmp_tree = root;
   reduce_param(tmp_tree);
   print_tree(root);
   //reduce_code(root);
 }
