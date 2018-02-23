/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:05:59 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 21:13:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
static unsigned int		count_champs(t_header *champs)
{
	int		i;

	i = 0;
	while (champs && i <= 2)
	{
		if (!champs->next)
	ft_putendl("################");
		champs = champs->next;
		i++;
	}
	return (i);
}*/

static void				init(t_vm *env)
{
	env->cycle = 0;
	env->check = 0;
	env->max_check = MAX_CHECKS;
	env->nbr_live = NBR_LIVE;
	env->c_delta = CYCLE_DELTA;
	env->c_todie = CYCLE_TO_DIE;
	ft_bzero((void*)env->memory, MEM_SIZE);
//	env->nb_player = count_champs(env->champion);
	env->nb_player = 2;
	env->process = NULL;
	env->ll_champ = NULL;
	env->champion = NULL;
	env->dump = -1;
}

static void				init_op_tab(t_op *op_tab)
{
/*	(*op_tab)[0] = &vm_live;
	(*op_tab)[1] = &vm_ld;*/
	op_tab[2] = &vm_st;
/*	(*op_tab)[3] = &vm_add;
	(*op_tab)[4] = &vm_sub;
	(*op_tab)[5] = &vm_and;
	(*op_tab)[6] = &vm_or;
	(*op_tab)[7] = &vm_xor;
	(*op_tab)[8] = &vm_zjump;
	(*op_tab)[9] = &vm_ldi;
	(*op_tab)[10] = &vm_sti;
	(*op_tab)[11] = &vm_fork;
	(*op_tab)[12] = &vm_lld;
	(*op_tab)[13] = &vm_lldi;
	(*op_tab)[14] = &vm_lfork;
	(*op_tab)[15] = &vm_aff;*/
}

static void				init_process(t_header *champ, t_vm *env)
{
	unsigned int	pc;

	pc = 0;
	while (champ)
	{
		if (env->process)
			pc = (MEM_SIZE / env->nb_player) + env->process->pc;
		add_process(&env->process, new_process(env->process, pc, env));
		env->process->champ = champ;
		env->process->reg[0] = champ->number;
		env->process->inst = env->memory[env->process->pc];
		set_cooldown(env->process, env);
		champ = champ->next;
	}
}

int						main(int ac, char **av)
{
	t_vm			env;
	t_op			*op_tab;

	if (!(op_tab = (t_op*)ft_memalloc(sizeof(t_op) * 16)))
		ft_exit(strerror(errno));
	init(&env);
	init_op_tab(op_tab);
	parsing(ac, av, &env, 0);
	init_process(env.champion, &env);
	run_cycle(op_tab, &env);
	ft_printf("Player %d(%s) win !\nThe game was finish at cycle %ld with %ld process");
	return (0);
}
