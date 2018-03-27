/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 06:03:03 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/27 21:42:13 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_memory		*free_factory(t_memory *save)
{
	t_memory	*tmp;

	tmp = NULL;
	if (save->prev)
		(save->prev)->next = save->next;
	if (save->prev)
		tmp = (save->prev);
	else if (save->next)
		tmp = save->next;
	ft_memdel((void **)&save->buf);
	ft_memdel((void **)&save);
	return (tmp);
}

char			*ft_realloc_line(char *data, int add_size, int old_size)
{
	char	*res;
	int		cmp;

	cmp = -1;
	res = ft_memalloc_exit(add_size + old_size + 2);
	while (++cmp < old_size + 1)
		res[cmp] = data[cmp];
	free(data);
	data = NULL;
	return (res);
}

t_memory		*load_save(t_memory *save, int fd, char **line, t_memory *recup)
{
	recup = save;
	if (save)
	{
		while (save->next && save->fd != fd)
			save = save->next;
		while (save->prev && save->fd != fd)
			save = save->prev;
		save->cmp_line = -1;
		if (save->fd == fd && save->cmp_buf < save->taille_buf)
			*line = ft_realloc_line(*line, save->taille_buf, save->cmp_line);
		if (save->fd == fd && save->cmp_buf < save->taille_buf)
			while (save->buf[++save->cmp_buf] != '\n' && save->cmp_buf <
					save->taille_buf)
				(*line)[++save->cmp_line] = save->buf[save->cmp_buf];
	}
	if (!save || save->fd != fd)
	{
		save = ft_memalloc_exit(sizeof(t_memory));
		save->fd = fd;
		save->next = recup;
		save->buf = ft_memalloc_exit(BUFF_SIZE + 1);
		save->cmp_line = -1;
	}
	return (save);
}

int				get_next_line(const int fd, char **line)
{
	static t_memory	*save = NULL;
	int				nb_read;

	nb_read = 0;
	if (fd < 0 || BUFF_SIZE < 1 || !line)
		return (-1);
	save = load_save(save, fd, line, NULL);
	while (save->buf[save->cmp_buf] != '\n' &&
	(nb_read = read(fd, save->buf, BUFF_SIZE)) > 0)
	{
		*line = ft_realloc_line(*line, nb_read, save->cmp_line);
		save->taille_buf = nb_read;
		save->cmp_buf = -1;
		while (++save->cmp_buf < nb_read && save->buf[save->cmp_buf] != '\n')
			(*line)[++save->cmp_line] = save->buf[save->cmp_buf];
	}
	if (save->buf[save->cmp_buf] == '\n' && save->cmp_buf != save->taille_buf)
		nb_read = 1;
	if (nb_read < 0 && !save->taille_buf)
		free_factory(save);
	nb_read = (nb_read > 0) ? 1 : 0;
	return (nb_read);
}
