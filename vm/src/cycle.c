/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/24 12:39:47 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

static void		dump_process(t_process *process, t_vm *env)
{
	if (env->option->dump_all >= 0)
	{
		ft_printf("nb process: %d\n", env->nb_process);
		while (process)
		{
			ft_printf("Player: %3d, ", process->champ->num);
			ft_printf("process ID: %7d, ", process->id);
			ft_printf("PC: %#08x, ", process->pc);
			ft_printf("inst: %2d, ", process->inst);
			ft_printf("carry : %d, ", process->carry);
			ft_printf("last_live: %d\n", process->last_live);
			process = process->next;
		}
	}
	exit(0);
}

static void		dump_memory(unsigned char mem[], t_process *process, t_vm *env)
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
		else if (i % 32 == 0)
			ft_printf("%#06x : ", i);
		if (tmp)
			ft_printf("\033[31;42m%02x\033[0m", (int)mem[i]);
		else
			ft_printf("%02x", (int)mem[i]);
		i++;
		if (i % 32 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	dump_process(process, env);
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
