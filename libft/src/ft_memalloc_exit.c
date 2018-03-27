/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 23:54:20 by gcollett          #+#    #+#             */
/*   Updated: 2017/12/13 00:00:12 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc_exit(size_t size)
{
	size_t	t;
	char	*str;

	t = -1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		exit(0);
	while (++t < size)
		str[t] = '\0';
	return (str);
}
