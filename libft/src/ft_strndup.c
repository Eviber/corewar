/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:42:32 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/28 14:22:03 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char				*ft_strndup(const char *s1, size_t n)
{
	char	*res;

	res = malloc(sizeof(char) * (n + 1));
	if (res)
	{
		ft_memcpy(res, s1, n);
		res[n] = '\0';
	}
	return (res);
}
