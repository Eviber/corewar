/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/24 15:18:01 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		search_inst(char *src, t_env *env)
{
	int		nb_param;
	size_t	fin_src;
	char	octal;
	int		cmp;

	nb_param = 0;
	cmp = -1;
	octal = 0;
	fin_src = find_next_instruction(src + env->index);
	cmp = -1;
	while (++cmp < 16 && ft_strncmp(src + env->index,
				env->op[cmp].name, fin_src))
		;
	if (cmp < 16)
	{
		env->index += fin_src;
		env->pos_last_inst = env->pos;
		get_param(env->op[cmp], src, env);
		return (1);
	}
	src[env->index + fin_src] = '\0';
	ft_error(env, src + env->index, 7);
	return (0);
}

void	read_champ(t_env *env, char *line)
{
	int		state;
	long	next_space;
	long	next_label_token;

	state = 0;
	next_space = find_next_instruction(line);
	next_label_token = find_next(line, LABEL_CHAR);
	while (line[++env->index] && line[env->index] !=
			COMMENT_CHAR && state != 2 && !env->error
			&& line[env->index] != COMMENT_CHAR)
	{
		if (ft_isspace(line[env->index]))
			;
		else if (state == 0 && is_label(line, env->index))
		{
			new_label(env, line, ft_strchr(line + env->index,
						LABEL_CHAR) - line, env->label);
			env->index += (ft_strchr(line + env->index, LABEL_CHAR) - line);
			state = 1;
		}
		else if (state != 2 && search_inst(line, env) && (state = 2))
			;
		else
			ft_error(env, NULL, 1);
	}
}

t_env	*init_env(int option, t_env *last_env)
{
	t_env	*env;
	long	magic;

	magic = COREWAR_EXEC_MAGIC;
	if (option == 1)
	{
		env = ft_memalloc_exit(sizeof(t_env));
		env->op = get_opt();
	}
	else if ((env = last_env))
	{
		ft_memdel((void **)&env->res);
		ft_memdel((void **)&env->champ);
		env->line = 0;
		env->state = 0;
		env->error = 0;
	}
	env->taille = PROG_NAME_LENGTH + COMMENT_LENGTH +
		sizeof(COREWAR_EXEC_MAGIC) + sizeof(long) + 4;
	env->label = NULL;
	env->res = ft_memalloc_exit(env->taille);
	env->champ = ft_memalloc_exit(40);
	env->size_champ = 40;
	fill_memory(env->res, magic, sizeof(COREWAR_EXEC_MAGIC), 0);
	return (env);
}

/*
** env->state
** 0 = start
** 1 = search att;
** 2 = Header valid go read the body
*/

char	*read_file(char *file, t_env *env)
{
	char	*line;
	int		fd;
	long	tmp;

	tmp = 0;
	line = ft_memalloc_exit(CHAMP_MAX_SIZE);
	fd = open(file, O_RDONLY);
	if (fd > 0)
		while (get_next_line(fd, &line) > 0 && ++env->line && !env->error)
		{
			env->index = -1;
			if (env->state < 2)
				read_attribut(env, line);
			else if (env->state == 2 && (env->state = 3))
				env->pos = 0;
			else if (env->state == 3)
				read_champ(env, line);
			ft_memdel((void **)&line);
		}
	if (fd <= 0 && (env->error = 1))
		ft_dprintf(2, "Open error on : %s\n", file);
	check_error(env);
	fill_length_file(env);
	check_label(env, NULL);
	return (env->res);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_env	*env;

	if (argc < 2)
		write(2, "Usage : ./asm file.s\n", 21);
	else if ((env = init_env(1, NULL)))
		while (--argc > 0)
		{
			switch_extension(env, argv[argc], ".cor");
			if (fd < 0 && (env->error = 1))
				ft_dprintf(2, "Open error for creation of %s\n", env->name);
			read_file(argv[argc], env);
			if (env->state == 3 && !env->error)
			{
				fd = open(env->name, O_RDWR | O_CREAT | O_TRUNC, 0666);
				ft_printf("Writing output program to %s\n", env->name);
				write(fd, env->res, env->taille);
				write(fd, env->champ, env->pos);
			}
			close(fd);
			env = init_env(2, env);
		}
	return (0);
}
