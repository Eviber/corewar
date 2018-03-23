/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checK_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:12:02 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/22 19:12:03 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

void  check_line(t_node *code, char *line)
{
  t_node *node_line;
  int i;

  i = -1;
  node_line = create_node(LINE, NULL);
  add_child(code, node_line);
  while (line[++i] && line[i] != COMMENT_CHAR)
  {
    
  }
}
