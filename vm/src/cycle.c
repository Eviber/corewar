/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:12:20 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/24 16:23:46 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"
#include <math.h>

static void		get_rgb(t_rgb *color, )
{
	color->r += 10;
	if (color->r < 50)
		color->r += 50;
	color->g += 20;
	if (color->g < 65)
		color->g += 65;
	color->b += 30;
	if (color->b < 80)
		color->b += 800;
/*	if (color->r < 255)
		color->r = color->r + 25 > 255 ? 255 : color->r + 25;
	if (color->r >= 255 && color->g < 255)
		color->r = color->g + 25 > 255 ? 255 : color->r + 25;
	if (color->g >= 255 && color->b < 255)
		color->r = color->b + 25 > 255 ? 255 : color->r + 25;
	if (color->g == 255 && color->b == 255 && color->r > 50)
		color->r = color->r - 25 < 50 ? 50 : color->r - 25;
	else if (color->r == 50 && color->b == 255 && color->g > 50)
		color->g = color->g - 25 < 50 ? 50 : color->g - 25;
	else if (color->r == 50 && color->g == 50 && color->b > 50)
		color->b = color->b - 25 < 50 ? 50 : color->b - 25;*/
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
			get_rgb(&color);
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
	t_process		*tmp;

	i = 0;
	ft_putchar('\n');
	while (i < MEM_SIZE)
	{
		tmp = process;
		while (tmp && tmp->pc != i)
			tmp = tmp->next;
		if (i == 0)
			ft_putstr("0x000000 : ");
		else if (i % 32 == 0)
			ft_printf("%#08x : ", i);
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
