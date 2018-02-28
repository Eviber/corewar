/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:23:05 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/24 23:57:24 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_zjmp(t_process *process, t_vm *env)
{
	int		p_one;

	if (process->carry == 1)
	{
		get_param_value(process->pc + 1, 2, &p_one, env);
		process->pc += (((short)p_one) % IDX_MOD);
	}
	else
		process->pc += 3;
}
