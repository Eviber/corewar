/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/10 17:36:49 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

static void		dump_memory(unsigned char memory[], t_process *process, t_vm *env)
{
	unsigned long	i;
	t_process		*tmp;

	i = 0;
	ft_putchar('\n');
	while (i < MEM_SIZE)
	{
		tmp = process;
		while (tmp && tmp->pc != i)
			tmp = tmp->next;
		if (i == 0)
			ft_putstr("0x0000 : ");
		else if (i % 64 == 0)
			ft_printf("%#06x : ", i);
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
	ft_printf("nb process: %d\n", env->nb_process);
	while (process)
	{
		ft_printf(\
"Player: %2d, process ID: %3d, PC: %#06x, inst: %2d, carry : %d, last_live: %d\n", \
process->champ->num, process->id, process->pc, process->inst, process->carry, process->last_live);
		process = process->next;
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
			dump_memory(env->memory, env->process, env);
		current = env->process;
		while (current)
			current = exec_process(current, op_tab, env);
		if (--(env->curr_c_todie) <= 0)
			check_process(&last_period, env->process, env);
		(env->cycle)++;
	}
}
