/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 23:06:13 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 14:15:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_process(unsigned long *last_period, t_process *process, t_vm *env)
{
	static unsigned long	old_nbr_live = 0;

	while (process)
	{
		if (env->cycle - process->last_live >= env->c_todie)
			del_process(&env->process, process);
		process = process->next;
	}
	if (env->nbr_live - old_nbr_live >= NBR_LIVE)
	{
		env->c_todie -= CYCLE_DELTA;
		env->max_check = MAX_CHECKS;
	}
	else if (--env->max_check <= 0)
	{
		env->c_todie -= CYCLE_DELTA;
		env->max_check = MAX_CHECKS;
	}
	*last_period = env->cycle;
	old_nbr_live = env->nbr_live;
}
