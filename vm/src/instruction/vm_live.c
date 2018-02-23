/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:40:00 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 20:52:06 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_live(t_process *process, t_vm *env)
{
	t_header		*tmp;
	int				player;

	player = get_param_value(process->pc + 1, 4, env);
	tmp = env->champion;
	while (tmp)
	{
		if (tmp->number == player)
		{
			tmp->last_live = env->cycle;
			tmp->nb_live += 1;
		}
		tmp = tmp->next;
	}
	process->last_live = env->cycle;
	process->pc += 5;
}
