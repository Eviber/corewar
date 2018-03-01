/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 23:06:13 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/01 19:31:16 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		check_cycle_todie(t_vm *env)
{
	static unsigned long	old_nbr_live = 0;

	if (env->nbr_live - old_nbr_live >= NBR_LIVE)
	{
		env->c_todie -= CYCLE_DELTA;
		env->max_check = MAX_CHECKS;
		if ((env->verbose & SHOW_CYCL))
			ft_printf("Cycle to die is now %d\n", env->c_todie);
	}
	else if (--env->max_check <= 0)
	{
		env->c_todie -= CYCLE_DELTA;
		env->max_check = MAX_CHECKS;
		if ((env->verbose & SHOW_CYCL))
			ft_printf("Cycle to die is now %d\n", env->c_todie);
	}
	old_nbr_live = env->nbr_live;
}

void			check_process(unsigned long *last_period, t_process *process, t_vm *env)
{
	while (process)
	{
		if (process->last_live < *last_period || !process->last_live || \
		env->c_todie <= 0)
		{
			if ((env->verbose & SHOW_DEAT))
				ft_printf("Process %ld hasn't lived for %d cycles (CTD %d)\n",\
				process->id, env->cycle - process->last_live, env->c_todie);
			del_process(&env->process, process);
			(env->nb_process)--;
		}
		process = process->next;
	}
	check_cycle_todie(env);
	*last_period = env->cycle;
	env->curr_c_todie = env->c_todie;
}
