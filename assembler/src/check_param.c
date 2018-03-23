/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:12:02 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/22 19:12:03 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

static void wich_param(t_node *node_param, char **param)
{
  t_node *new_param;
  int i;

  i = 0;
  while((*param)[i] && !ft_isspace((*param)[i]) &&
  (*param)[i] != COMMENT_CHAR && (*param)[i] != SEPARATOR_CHAR)
    i++;
  if (**param == 'r')
    new_param = create_node(REG, ft_strndup(*param, i));
  else if (**param == DIRECT_CHAR)
    new_param = create_node(DIRECT, ft_strndup(*param, i));
  else
    new_param = create_node(IND, ft_strndup(*param, i));
  add_child(node_param, new_param);
  *param = *param + i;
  if (**param)
    (*param)++;
  while(**param && ft_isspace(**param) && **param != COMMENT_CHAR
  && **param != SEPARATOR_CHAR)
    (*param)++;
}

void check_param(t_node *node_param, char *param)
{
  t_node *new_param;
  t_node *node_sep;
  int i;

  i = 0;
  while(param[i] && !ft_isspace(param[i]) && param[i] != COMMENT_CHAR &&
  param[i] != SEPARATOR_CHAR)
    i++;
  new_param = create_node(PARAM, NULL);
  add_child(node_param, new_param);
  if (param[i] == SEPARATOR_CHAR)
  {
    node_sep = create_node(SEP, NULL);
    add_child(node_param, node_sep);
  }
  wich_param(new_param, &param);
  if (*param && *param != COMMENT_CHAR)
  {
    new_param = create_node(PARAM, NULL);
    add_child(node_param, new_param);
    check_param(new_param, param);
  }
}
