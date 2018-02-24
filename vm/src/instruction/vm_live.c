/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:40:00 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/24 23:52:56 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_live(t_process *process, t_vm *env)
{
	t_header		*tmp;
	int				player;

	get_param_value(process->pc + 1, 4, &player, env);
	tmp = env->champion;
	while (tmp && tmp->number != player)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->last_live = env->cycle;
		tmp->nb_live += 1;
		env->ll_champ = tmp;
	}
	env->nbr_live += 1;
	process->last_live = env->cycle;
	process->pc += 5;
}
