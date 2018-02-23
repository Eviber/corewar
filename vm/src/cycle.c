/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/22 21:02:30 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		dump_memory(unsigned char memory[])
{
	unsigned long	i;

	i = 0;
	while (i < MEM_SIZE)
	{
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

	while (env->process)
	{
		if (env->dump >= 0 && env->cycle == (unsigned long)env->dump)
			dump_memory(env->memory);
		if (env->cycle - last_period >= env->c_todie)
			check_process(&last_period, env->process, env);
		current = env->process;
		while (current)
		{
			exec_process(current, op_tab, env);
			current = current->next;
		}
		(env->cycle)++;
	}
}
