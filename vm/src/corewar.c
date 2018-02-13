/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:05:59 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/13 20:19:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

static void		init(t_vm *env)
{
	int		i;

	i = -1;
	env->check = 0;
	env->max_check = MAX_CHECKS;
	env->nbr_live = NBR_LIVE;
	env->c_delta = CYCLE_DELTA;
	env->c_todie = CYCLE_TO_DIE;
	ft_bzero((void*)env->memory, MEM_SIZE);
}

int				main(int ac, char **av)
{
	t_vm	env;

	init(&env);
	return (0);
}
