/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/04/05 18:25:53 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_test_num_player(t_header *tmp, long num, t_header *player, int error)
{
	while (tmp)
	{
		if (tmp != player)
		{
			if (tmp->num_lock && tmp->num_lock == player->num_lock)
			{
				ft_dprintf(2, "Two champions have the same id\n");
				exit(1);
			}
			else if (tmp->num == num && tmp->num_lock != num)
			{
				error = 1;
				tmp->num++;
			}
		}
		tmp = tmp->next;
	}
	return (error);
}

void	ft_confirm_num_player(t_vm *env)
{
	t_header	*tmp;
	int			error;

	error = 1;
	while (error == 1)
	{
		tmp = env->champion;
		error = 0;
		while (tmp)
		{
			if (tmp->num_lock)
				tmp->num = tmp->num_lock;
			error = ft_test_num_player(env->champion, tmp->num, tmp, error);
			tmp = tmp->next;
		}
	}
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
	if (tmp->magic != COREWAR_EXEC_MAGIC)
		ft_exit("MAGIC ne correspond pas\n");
	if (tmp->prog_size > CHAMP_MAX_SIZE)
		ft_exit("Champion too big\n");
	if (!tmp->prog_size)
		ft_exit("Champion doesn't have a size\n");
}

void	ft_choose_num_player(t_vm *env, int num_k)
{
	t_header	*tmp;
	long		max;

	max = 0;
	tmp = env->champion;
	while (tmp->next)
	{
		max = ((max < tmp->num) ? tmp->num : max);
		tmp = tmp->next;
	}
	if (num_k)
	{
		tmp->num = num_k;
		tmp->num_lock = num_k;
	}
	else
		tmp->num = max + 1;
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
	ft_choose_num_player(env, num);
	ft_fill_header(tmp, line, -1, 0);
	ft_strdel(&line);
}
