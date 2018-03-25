/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:40:00 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/25 14:16:38 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_live(t_process *process, t_vm *env)
{
	t_header		*tmp;
	int				player;

	if ((env->option->verbose & SHOW_MOVE))
		show_pc_mov(process->pc, process->pc + 5, 5, env);
	get_param_value((process->pc + 1) % MEM_SIZE, 4, &player, env);
	tmp = env->champion;
	while (tmp && tmp->num != player)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->last_live = env->cycle;
		(tmp->nb_live)++;
		(tmp->nb_live_p)++;
		env->ll_champ = tmp;
		if ((env->option->verbose & SHOW_LIVE))
			ft_printf("Player %d (%s) is said to be alive\n", \
			tmp->num, tmp->prog_name);
	}
	env->nbr_live += 1;
	process->last_live = env->cycle;
	process->pc += 5;
}
