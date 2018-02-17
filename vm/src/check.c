/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 23:06:13 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/17 23:39:11 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	check_process(unsigned long *last_period, t_process *process, t_vm *env)
{
	static unsigned long	old_nbr_live = 0;
	static int				nb_check = 0;

	while (process)
	{
		if (env->cycle - process->last_live >= env->c_todie)
			del_process(&env->process, process);
		process = process->next;
	}
	if (nbr_live - old_nbr_live >= NBR_LIVE)
	{
		env->c_todie -= CYCLE_DELTA;
		nb_check = 0;
	}
	else if (++nb_check >= MAX_CHECKS)
	{
		env->c_todie -= CYCLE_DELTA;
		nb_check = 0;
	}
	*last_period = env->cycle;
	old_nbr_live = env->nbr_live;
}
