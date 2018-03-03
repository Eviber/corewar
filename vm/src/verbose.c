/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:17:42 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/02 16:01:43 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	show_pc_mov(unsigned int old_pc, unsigned int new_pc, int len, \
t_vm *env)
{
	int		i;

	i = -1;
	ft_printf("ADV %d (%#06x -> %#06x)", len, old_pc, new_pc);
	while (++i < len)
	{
		if (i + 1 >= len)
			ft_printf(" %02x\n", env->memory[(old_pc + i) % MEM_SIZE]);
		else
			ft_printf(" %02x", env->memory[(old_pc + i) % MEM_SIZE]);
	}
}
