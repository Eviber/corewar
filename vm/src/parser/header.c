/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/23 14:11:48 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_print_head(t_vm *env, int cmp)
{
	t_header	*tmp;

	tmp = env->champion;
	ft_printf("dump = %ld\n", env->option->dump);
	ft_printf("visu = %ld\n", env->option->visu);
	ft_printf("nb_player = %ld\n", env->nb_player);
	while (tmp)
	{
		ft_printf("\nmagic = %x\n", tmp->magic);
		ft_printf("num = %d\n", tmp->num);
		ft_printf("name = %s\n", tmp->prog_name);
		ft_printf("taille = %lu\n", tmp->prog_size);
		ft_printf("comment = %s\n\n", tmp->comment);
		tmp = tmp->next;
	}
	while (cmp++ < MEM_SIZE - 1)
	{
		if (cmp && !(cmp % 64))
			ft_printf("\n");
		if (env->memory[cmp] < 16)
			ft_printf("0");
		ft_printf("%x ", env->memory[cmp]);
	}
	ft_printf("\n");
}

void	ft_fill_header(t_header *tmp, char *line, unsigned long i, int error)
{
	while (++i < COMMENT_LENGTH + 4 + 8 + PROG_NAME_LENGTH && !error)
	{
		if (i < sizeof(unsigned int))
			tmp->magic = tmp->magic * 256 + (unsigned char)line[i];
		else if (i < PROG_NAME_LENGTH + sizeof(unsigned int))
			tmp->prog_name[i - sizeof(unsigned int)] = line[i];
		else if (i < PROG_NAME_LENGTH + sizeof(long) + sizeof(unsigned int))
			tmp->prog_size = tmp->prog_size * 256 + (unsigned char)line[i];
		else
			tmp->comment[i - 4 - 8 - PROG_NAME_LENGTH] = line[i];
	}
	if (error)
		exit(1);
	ft_printf("tmp->name = %s\n", tmp->prog_name);
	if (tmp->magic != COREWAR_EXEC_MAGIC)
		ft_exit("MAGIC ne correspond pas\n");
	if (tmp->prog_size > CHAMP_MAX_SIZE)
		ft_exit("Le champion est trop long\n");
}

void	ft_choose_num_player(t_vm *env, int num_k, int fail, int max)
{
	t_header	*tmp;
	t_header	*tmp2;
	int			num;

	num = 0;
	while (fail == 1 && !(fail = 0))
	{
		tmp = env->champion;
		while (tmp->next && (tmp2 = env->champion) && (fail == 0))
		{
			if (tmp->num == num_k && (fail = 1))
				tmp->num++;
			num = tmp->num;
			max = ((max < tmp->num) ? num : max);
			while (tmp2->next && (fail == 0))
			{
				if (tmp != tmp2 && (tmp2->num == num_k || tmp2->num == num) && (fail = 1))
					tmp2->num++;
				max = ((max < tmp->num) ? num : max);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	}
	tmp->num = ((num_k) ? num_k : max + 1);
}

void	ft_init_header(t_vm *env, char *line, int start, char **av)
{
	t_header	*tmp;
	int			num;

	num = 0;
	if (env->champion && (tmp = env->champion))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_header));
		tmp = tmp->next;
	}
	else
	{
		env->champion = ft_memalloc(sizeof(t_header));
		tmp = env->champion;
	}
	if (start > 2 && !(ft_strcmp(av[start - 2], "-n")))
		num = ft_atoi(av[start - 1]);
	ft_choose_num_player(env, num, 1, 0);
	ft_fill_header(tmp, line, -1, 0);
	ft_strdel(&line);
}
