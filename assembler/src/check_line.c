/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:12:02 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/22 19:12:03 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

static void check_fct(t_node *node_inst, char **inst)
{
  t_node *node_fct;
  int i;

  i = 0;
  while ((*inst)[i] && !ft_isspace((*inst)[i]) && (*inst)[i] != COMMENT_CHAR)
    i++;
  node_fct = create_node(FCT, ft_strndup(*inst, i));
  add_child(node_inst, node_fct);
  *inst = *inst + i;
  while (**inst && ft_isspace(**inst))
    (*inst)++;
}

static void register_inst(t_node *node_inst, char *inst)
{
  t_node *node_param;

  check_fct(node_inst, &inst);
  if (*inst && *inst != COMMENT_CHAR)
  {
    node_param = create_node(PARAM, NULL);
    add_child(node_inst, node_param);
    check_param(node_param, inst);
  }
}

static void check_label(t_node *node_line, char **line) // check label chars ? enfin utiliser le dfine LABELCHARS
{
  t_node *node_label;
  int i;

  i = 0;
  while ((*line)[i] && !ft_isspace((*line)[i]) && (*line)[i] != COMMENT_CHAR)
    i++;
  if (i > 1 && (*line)[i - 1] == LABEL_CHAR)
  {
    node_label = create_node(LABEL, ft_strndup(*line, i - 1));
    add_child(node_line, node_label);
    *line = *line + i;
    while (**line && ft_isspace(**line))
      (*line)++;
  }
}

void  check_line(t_node *node_line, char *line)
{
  t_node *node_inst;

  check_label(node_line, &line);
  if (*line && *line != COMMENT_CHAR)
  {
    node_inst = create_node(INST, NULL);
    add_child(node_line, node_inst);
    register_inst(node_inst, line);
  }
}
