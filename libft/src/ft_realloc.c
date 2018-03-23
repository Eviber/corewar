/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:29:06 by gcollett          #+#    #+#             */
/*   Updated: 2017/01/16 06:30:01 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *str, size_t len_str, int add_bytes,
		size_t reading_speed)
{
	int		a;
	void	*new;

	if (!str)
		return (NULL);
	a = -1;
	if (0 < len_str + add_bytes &&
			!(new = ft_memalloc((len_str + add_bytes) * reading_speed)))
	{
		ft_memdel(&str);
		return (NULL);
	}
	if (0 <= add_bytes)
	{
		while (++a < (int)len_str)
			((char *)new)[a] = ((char *)str)[a];
	}
	else
		while (++a < ((int)len_str + add_bytes))
			((char *)new)[a] = ((char *)str)[a];
	ft_memdel(&str);
	return (new);
}
