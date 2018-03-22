/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:48:10 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/22 15:48:14 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

static void   ft_realloc_line(char **res, char *buf, int old_s, int add_s)
{
  char *result;
  int i;

  i = -1;
  result = ft_memalloc(old_s + add_s);
  if (!result)
    pexit("Malloc returned null\n", 1);
  while (++i < old_s)
    result[i] = (*res)[i];
  while (i++ < (old_s + add_s))
  {
    result[i] = buf[i - old_s];
    i++;
  }
  free(*res);
  *res = result;
}

static void fill_name(t_node *node, char *line, int fd, int i)
{
  char buf[400];
  int j;

  j = -1;
  while (line[i] || (get_next_line(fd, &line) > 0))
	{
    while (line[++i] && line[i]!= '"')
    {
        ++j;
        if (j % 400 == 0)
          ft_realloc_line(&node->name, buf, j - 400, 400);
        buf[j % 400] = line[i];
    }
    if (line[i] == '"')
      break;
    }
    if (line[i] != '"')
      pexit("Missing the end of an attribut\n", -2);
}

static void register_comment_command(t_node *header, char *line, int fd)
{
  t_node *comment_node;
  int i;

  i = 0;
  while (line[i] && line[i] != '"' && line[i] != '#')
    i++;
  if (line[i] != '"')
    pexit("Missing name after the name attribut\n", -2);
  comment_node = create_node(CMD_CMT, NULL);
  if (!header->children)
    create_child(header, comment_node);
  else
    add_next_child(header, comment_node);
  fill_name(comment_node, line, fd, i);
}

static void register_name_command(t_node *header, char *line, int fd)
{
  t_node *name_node;
  int i;

  i = 0;
  while (line[i] && line[i] != '"' && line[i] != '#')
    i++;
  if (line[i] != '"')
    pexit("Missing name after the name attribut\n", -2);
  name_node = create_node(CMD_NAME, NULL);
  if (!header->children)
    create_child(header, name_node);
  else
    add_next_child(header, name_node);
  fill_name(name_node, line, fd, i);
}

void			get_cmd(t_node *header,char *line, int fd)
{
	if (!ft_strncmp(line, ".name", 5))
		register_name_command(header, line, fd);
	else if (!ft_strncmp(line, ".comment", 8))
		register_comment_command(header, line, fd);
  else
    pexit("attribut invalid\n", -1); // doije faire le meme rendue que zaz ?
}
