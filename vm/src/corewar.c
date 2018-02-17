/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:05:59 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/17 23:54:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		init(t_vm *env)
{
	env->cycle = 0;
	env->check = 0;
	env->max_check = MAX_CHECKS;
	env->nbr_live = NBR_LIVE;
	env->c_delta = CYCLE_DELTA;
	env->c_todie = CYCLE_TO_DIE;
	ft_bzero((void*)env->memory, MEM_SIZE);
	env->nb_player = 0;
	env->process = NULL;
	env->champion = NULL;
	env->dump = -1;
}

static void		init_op_tab(t_op *op_tab)
{
	(*op_tab)[0] = &live;
	(*op_tab)[1] = &ld;
	(*op_tab)[2] = &st;
	(*op_tab)[3] = &add;
	(*op_tab)[4] = &sub;
	(*op_tab)[5] = &and;
	(*op_tab)[6] = &or;
	(*op_tab)[7] = &xor;
	(*op_tab)[8] = &zjump;
	(*op_tab)[9] = &ldi;
	(*op_tab)[10] = &sti;
	(*op_tab)[11] = &fork;
	(*op_tab)[12] = &lld;
	(*op_tab)[13] = &lldi;
	(*op_tab)[14] = &lfork;
	(*op_tab)[15] = &aff;
}

static int		init_process(t_header *champ, t_vm *env)
{
	unsigned int	pc;

	pc = 0;
	while (champ)
	{
		if (env->process)
			pc = (MEM_SIZE / env->nb_player) + env->process->pc;
		add_process(&env->process, new_process(env->process, pc, env));
		env->process->champ = champ;
		env->process.reg[0] = champ->number;
		champ = champ->next;
	}
}

int				main(int ac, char **av)
{
	t_vm			env;
	t_op			op_tab;
	t_process		*current;
	unsigned long	last_period;

	init(&env);
	init_op_tab(&op_tab);
	parsing(ac, av, &env, 0);
	init_process(env.champion, &env);
	last_period = 0;
	while (env.process)
	{
		(env.cycle)++;
		if (env.cycle - last_period >= env.c_todie)
			check_process(&last_period, env.process, &env);
		current = env.process;
		while (current)
		{
			exec_process(current, op_tab, &env);
			current = current->next;
		}
	}
	return (0);
}
