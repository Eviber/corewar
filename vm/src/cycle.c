/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/01 19:27:10 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		dump_memory(unsigned char memory[], t_process *process)
{
	unsigned long	i;
	t_process		*tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		tmp = process;
		while (tmp && tmp->pc != i)
			tmp = tmp->next;
		if (tmp)
			ft_printf("\033[31;42m%02x\033[0m", (int)memory[i]);
		else
			ft_printf("%02x", (int)memory[i]);
		i++;
		if (i % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	exit(0);
}

void			run_cycle(t_op *op_tab, t_vm *env)
{
	t_process		*current;
	unsigned long	last_period;

	last_period = 0;
	while (env->process)
	{
		if ((env->verbose & SHOW_CYCL))
			ft_printf("It is now cycle %d\n", env->cycle + 1);
		env->mem_mov = 0;
		if (env->dump >= 0 && env->cycle == (unsigned long)env->dump)
			dump_memory(env->memory, env->process);
		if (--(env->curr_c_todie) <= 0)
			check_process(&last_period, env->process, env);
		current = env->process;
		while (current)
			current = exec_process(current, op_tab, env);
		(env->cycle)++;
	}
}
