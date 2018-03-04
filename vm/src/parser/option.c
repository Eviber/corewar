/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:15:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_opt *get_opt(void)
{
  static t_opt    opt_tab[4] = {
  	{"dump", 1, 1, 1, 0},
  	{"n", 1, 1, 0, 1},
  	{"v", 1, 0, 1, 0},
  	{0, 0, 0, 0, 0} };

  return(opt_tab);
}

int search_opt(char *str, t_vm *env)
{
	int cmp;

	cmp = -1;
	while(++cmp < 3 && ft_strcmp(str + 1, env->option[cmp].name))
		;
	if (cmp > 2 && ft_dprintf(2, "%s is not a valid n\n", str))
		exit(1);
	return(cmp);
}

int opt_have_value(int pos, char **av, int cmp, t_vm *env)
{
	int i;

	i = -1;
	if (env->option[cmp].has_value && av[pos + 1])
	{
    if (env->option[cmp].value_can_be_negative && av[pos + 1][i + 1] == '-')
      ++i;
		while (av[pos + 1] && av[pos + 1][++i] && ft_isdigit(av[pos + 1][i]))
			;
		if ( av[pos + 1] && !(av[pos + 1][i]))
			return(1);
	}
	return(0);
}

int check_opt(int pos, char **av, t_vm *env)
{
	int cmp;

	cmp = search_opt(av[pos], env);
	if (opt_have_value(pos, av, cmp, env))
	{
		if (cmp == 0)
			env->dump = ft_atoi(av[pos + 1]);
		else if (cmp == 2)
			env->verbose = ft_atoi(av[pos + 1]);
		return (1);
	}
	if (env->option[cmp].value_needed && ft_dprintf(2, "option %s need a value\n", env->option[cmp].name))
		exit(1);
	else if (cmp == 2)
		env->verbose = 1;
	return(0);
}
