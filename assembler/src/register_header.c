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

static void   ft_realloc_line(t_node *node, char *buf, int old_s, int add_s)
{
  char *result;
  int i;

  i = -1;
  if (old_s < 0)
    old_s = 0;
  result = ft_memalloc(old_s + add_s + 1);
  if (!result)
    pexit("Malloc returned null\n", 1);
  while (++i < old_s)
    result[i] = node->name[i];
  while (i < (old_s + add_s))
  {
    result[i] = buf[i - old_s];
    i++;
  }
  free(node->name);
  node->name = result;
}

static void fill_name(t_node *node, char *line, int fd, int i)
{
  char buf[400];
  int j;

  j = 0;
  while ((line[i] || ((get_next_line(fd, &line) > 0) && !(i = 0)))
   && line[i] != '"')
	{
    while (line[i] && line[i] != '"')
    {
        buf[j % 400] = line[i];
        if (++j % 400 == 0)
          ft_realloc_line(node, buf, j - 400, 400);
        i++;
    }
    if (line[i] != '"' && j % 400 == 0)
      ft_realloc_line(node, buf, j - 400, 400);
    if (line[i] != '"')
      buf[j++ % 400] = '\n';
  }
  if (line[i] != '"')
    pexit("Missing the end of an attribut\n", -2);
  else if (j % 400)
      ft_realloc_line(node, buf, j - 400, j % 400);
}

static void register_command(t_node *header, char *line, int fd, int type)
{
  t_node *node;
  int i;

  i = 0;
  while (line[i] && line[i] != '"' && line[i] != '#')
    i++;
  if (line[i] != '"')
    pexit("Missing name after an attribut\n", -2);
  node = create_node(type, NULL);
  add_child(header, node);
  fill_name(node, line, fd, ++i);
  if (type == CMD_NAME && ft_strlen(node->name) > PROG_NAME_LENGTH)
    pexit("Champion name too long ", -3);
  if (type == CMD_CMT && ft_strlen(node->name) > COMMENT_LENGTH)
    pexit("Champion comment too long\n", -3);
}

void			get_cmd(t_node *header,char *line, int fd)
{
	if (!ft_strncmp(line, ".name", 5))
		register_command(header, line, fd, CMD_NAME);
	else if (!ft_strncmp(line, ".comment", 8))
		register_command(header, line, fd, CMD_CMT);
  else
    pexit("attribut invalid\n", -1);
}
