/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:03:33 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 21:29:23 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				check_peb(unsigned char peb, char **perm, int nb_param)
{
	int		param;
	char	current;

	param = -1;
	while (++param < nb_param)
	{
		current = (peb >> (8 - ((param + 1) * 2))) & IND_CODE;
		if (!(perm[param][current - 1]))
			return (1);
	}
	return (0);
}

unsigned int	get_param_value(unsigned int at, int len, t_vm *env)
{
	int				i;
	unsigned int	value;

	i = -1;
	value = 0;
	while (++i < len)
		value = (value << (8 * i)) + env->memory[at + i];
	return (value);
}

int				param_len(unsigned char peb, int mod, int nb_param)
{
	int		param;
	int		len;
	char	current;

	param = -1;
	len = 0;
	while (++param < nb_param)
	{
		current = (peb >> ((param + 1) * 2)) & IND_CODE;
		if (current == REG_CODE)
			len += 1;
		else if (current == DIR_CODE && mod == 1)
			len += 4;
		else
			len += 2;
			return (1);
	}
	return (0);
	
}
