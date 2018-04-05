/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/04/05 15:45:06 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"
#include <math.h>

static t_rgb	get_rgb(t_process *process, t_vm *env)
{
	t_rgb	color;
	int		step;

	step = 360 / ((env->nb_player > 3) ? env->nb_player + 1 : 3);
	color = vm_hsl(120 + process->champ->index_color * step, 75, 50);
	return (color);
}

static void		dump_process(t_process *process, t_vm *env)
{
	t_rgb	color;

	if (env->option->dump_all >= 0)
	{
		ft_printf("nb process: %d\n", env->nb_process);
		ft_printf("\033[4mPlayer | process ID | %-8s | inst | carry | %-10s\n",\
		"PC", "last live");
		ft_putstr("\033[0m");
		while (process)
		{
			color = get_rgb(process, env);
			ft_printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
			ft_printf("%-6d | ", process->champ->num);
			ft_printf("%10d | ", process->id);
			ft_printf("%#08x | ", process->pc);
			ft_printf("%-4d | ", process->inst);
			ft_printf("%-5d | ", process->carry);
			ft_printf("%10d", process->last_live);
			ft_putchar('\n');
			process = process->next;
			ft_putstr("\033[0m");
		}
	}
	exit(0);
}

static void		dump_memory(unsigned char mem[], t_process *process, t_vm *env)
{
	unsigned long	i;

	i = 0;
	ft_putchar('\n');
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_putstr("0x000000 : ");
		else if (i % 32 == 0)
			ft_printf("%#08x : ", i);
		ft_printf("%02x", (int)mem[i]);
		i++;
		if (i % 32 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	dump_process(process, env);
}

static void		kill_dead_process(t_process **todel, t_vm *env)
{
	unsigned long	i;
	size_t			list_len;
	t_process		*next;

	i = 0;
	next = NULL;
	list_len = 0;
	if (todel)
		next = *todel;
	while (next)
	{
		list_len++;
		next = next->next;
	}
	if (env->curr_c_todie > 0)
		while (todel && *todel && ++i <= list_len / env->curr_c_todie)
		{
			next = (*todel)->next;
			ft_memdel((void**)todel);
			*todel = next;
		}
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
		kill_dead_process(&env->killed_process, env);
		(env->cycle)++;
	}
	env->mem_mov = 1;
}
