/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/05 20:55:51 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

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
	while (process)
	{
		ft_printf("Process ID: %d, Instruction = %d, PC = %d, PLayer = %d, Carry = %d\n", process->id, process->inst, process->pc, process->champ->num, process->carry);
		process= process->next;
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
		if ((env->option->verbose & SHOW_CYCL))
			ft_printf("It is now cycle %d\n", env->cycle + 1);
		if (env->option->visu)
			env->option->visu = visu();
		env->mem_mov = 0;
		if (env->option->dump >= 0 && \
		env->cycle == (unsigned long)env->option->dump)
			dump_memory(env->memory, env->process);
		current = env->process;
		while (current)
			current = exec_process(current, op_tab, env);
		if (--(env->curr_c_todie) <= 0)
			check_process(&last_period, env->process, env);
		(env->cycle)++;
	}
}
