/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/28 18:44:51 by vsporer          ###   ########.fr       */
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
	while (process)
	{
		ft_printf("Player: %d, PC = %d\nCarry = %d\n", process->champ->num, process->pc, process->carry);
		process = process->next;
	}
	exit(0);
}

void			run_cycle(t_op *op_tab, t_vm *env)
{
	long			c_todie;
	t_process		*current;
	unsigned long	last_period;

	last_period = 0;
	c_todie = CYCLE_TO_DIE;
	while (env->process)
	{
		c_todie--;
		if (env->option->dump >= 0 && env->cycle == (unsigned long)env->option->dump)
			dump_memory(env->memory, env->process);
		if (c_todie <= 0)
		{
			check_process(&last_period, env->process, env);
			c_todie = env->c_todie;
		}
		current = env->process;
		while (current)
		{
			exec_process(current, op_tab, env);
			current = current->next;
		}
		(env->cycle)++;
	}
}
