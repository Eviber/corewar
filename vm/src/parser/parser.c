/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:15:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int				rd(char *line, t_vm *env, unsigned long max, unsigned long pos)
{
	unsigned long cmp;

	cmp = -1;
	while (++cmp < max)
		env->memory[pos + cmp] = line[cmp];
	return (0);
}

static unsigned long	check_arg(int ac, char **av, t_vm *env)
{
	unsigned long	nb_champ;
	int				error;
	int				i;

	i = 0;
	error = 0;
	nb_champ = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' &&
				(!ft_strcmp(av[i] + 1, "dump") || !ft_strcmp(av[i] + 1, "n")))
		{
			if (!ft_strcmp(av[i] + 1, "dump"))
				env->dump = ft_atoi(av[++i]);
			else
				i++;
		}
		else
			nb_champ++;
	}
	if (nb_champ > MAX_PLAYERS)
		ft_exit("Too many player\n");
	if (nb_champ == 0)
		ft_exit("No player\n");
	return (nb_champ);
}

static char 			*get_header(int fd)
{
	long	taille;
	long	cmp;
	char	*line;


	taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(int) + sizeof(long);
	line = ft_memalloc(taille + 1);
	if ((cmp = read(fd, line, taille + 4)) < taille)
		ft_exit((fd <= 0) ? "Fichier inacessible\n" : "Fichier trop petit\n");
	return (line);
}

void					parsing(int ac, char **av, t_vm *env, int cmp)
{
	unsigned long	nb_champ;
	char			*line;
	int				fd;
	int				start;

	start = 0;
	line = ft_memalloc(CHAMP_MAX_SIZE);
	nb_champ = check_arg(ac, av, env) + 1;
	if (ac < 2)
		ft_exit("Usage: ./vm [champion.cor]");
	else if ((ac = nb_champ))
		while (--nb_champ > 0)
		{
			while (av[++start][0] == '-')
				start += 1;
			fd = open(av[start], O_RDONLY);
			ft_init_header(env, get_header(fd), start, av);
			cmp = read(fd, line, CHAMP_MAX_SIZE);
			rd(line, env, cmp, (nb_champ - 1) * (MEM_SIZE / (ac - 1)));
			close(fd);
		}
	ft_memdel((void**)&line);
	ft_print_head(env, -1);
}
