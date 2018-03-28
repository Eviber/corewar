/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 17:16:13 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/28 12:17:11 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft.h>
# include <corewar.h>

typedef struct		s_roquet
{
	int				type;
	long			pos;
	long			value;
	int				i;
	int				j;
	int				size_max;
	struct s_roquet	*next;
}					t_roquet;

typedef struct		s_label
{
	char			*name;
	long			index;
	t_roquet		*appel;
	struct s_label	*next;
}					t_label;

typedef struct		s_op
{
	char			*name;
	int				nb_params;
	short			type;
	int				has_octal;
	int				half_dir_size;
	int				opcode;
}					t_op;

typedef struct		s_env
{
	char			*name;
	long			size_champ;
	char			*res;
	char			*champ;
	int				error;
	long			pos;
	long			pos_last_inst;
	long			index;
	int				state;
	long			line;
	size_t			taille;
	t_label			*label;
	t_op			*op;
	struct s_env	*next;
}					t_env;

/*
** attribut
*/
void				read_attribut(t_env *env, char *line);

/*
** param
*/

t_op				*get_opt(t_op *op_tab);
void				get_param(t_op op, char *src, t_env *env);

/*
** attribut
*/

void				read_attribut(t_env *env, char *line);

/*
** label
*/

int					get_label(char *name, t_env *env, int i, int size);
void				new_label(t_env *env, char *src, size_t end_src,
		t_label *tmp);
int					is_label(char *src, int start);
void				check_label(t_env *env, t_label *tmp);
void				clean_label(t_env *env, t_label *tmp);

/*
** struct_tool
*/

void				switch_extension(t_env *env, char *src,
		char *new_extension);
void				fill_length_file(t_env *env);
int					find_next(char *src, char car);
int					find_next_instruction(char *src);
void				check_error(t_env *env);

/*
** tool
*/

void				load_new_roquet(t_label *target, t_env *env, int size);
void				fill_memory(char *mem, long value, int size, int start);
void				*ft_memalloc_exit(size_t size);
void				memory_manager(t_env *env, int size);
int					check_int_param(char *str, t_env *env, long i);

/*
** exit
*/

void				ft_error(t_env *env, char *name, int error);
void				clean_env(t_env *env, int option);

#endif
