/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/04/05 18:22:41 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "vm.h"

t_opt	*get_opt(void)
{
	static t_opt	opt_tab[NB_OPTION + 1] = {
		{"dump", 1, 1, 1, 0},
		{"n", 1, 1, 0, 1},
		{"v", 1, 0, 1, 0},
		{"g", 0, 0, 0, 0},
		{"f", 0, 0, 0, 0},
		{"dump_all", 1, 1, 1, 0},
		{0, 0, 0, 0, 0} };

	return (opt_tab);
}

int		search_opt(char *str, t_vm *env)
{
	int cmp;

	cmp = -1;
	if (str + 1)
		while (++cmp < NB_OPTION && ft_strcmp(str + 1, env->opt[cmp].name))
			;
	if ((!(str + 1) || cmp > NB_OPTION - 1) &&
			ft_dprintf(2, "%s is not a valid option\n", str))
		exit(1);
	return (cmp);
}

void	check_if_number_is_valid(long num, int cmp)
{
	if (cmp == 1 && (num == 0) &&
	ft_dprintf(2, "0 is not a valid number of player\n"))
		exit(1);
	if (cmp == 2 && (num != SHOW_LIVE && num != SHOW_CYCL
		&& num != SHOW_DEAT && num != SHOW_MOVE))
	{
		ft_dprintf(2, "%d is not a valid number for verbose option\n", num);
		exit(1);
	}
}

int		opt_have_value(int pos, char **av, int cmp, t_vm *env)
{
	int i;

	i = -1;
	if (env->opt[cmp].has_value && av[pos + 1])
	{
		if (env->opt[cmp].value_can_be_negative && av[pos + 1][i + 1] == '-')
			++i;
		while (av[pos + 1] && av[pos + 1][++i] && ft_isdigit(av[pos + 1][i]))
			;
		check_if_number_is_valid(ft_atol(av[pos + 1]), cmp);
		if (av[pos + 1] && !(av[pos + 1][i]))
			return (1);
	}
	return (0);
}

int		check_opt(int pos, char **av, t_vm *env)
{
	int cmp;

	cmp = search_opt(av[pos], env);
	if (opt_have_value(pos, av, cmp, env))
	{
		if (cmp == 0)
			env->option->dump = ft_atol(av[pos + 1]);
		else if (cmp == 2)
			env->option->verbose = ft_atoi(av[pos + 1]);
		else if (cmp == 5 && (env->option->dump_all = 1))
			env->option->dump = ft_atol(av[pos + 1]);
		return (1);
	}
	if (cmp == 3)
		env->option->visu = SDL_WINDOW_FULLSCREEN;
	if (cmp == 4)
		env->option->visu = SDL_WINDOW_RESIZABLE;
	if (env->opt[cmp].value_needed && ft_dprintf(2,
				"option %s needs a value\n", env->opt[cmp].name))
		exit(1);
	else if (cmp == 2)
		env->option->verbose = 1;
	return (0);
}
