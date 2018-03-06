/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/03/06 15:13:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"!' ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_0123456789."

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct			s_header
{
	int					num;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned long		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned long		last_live;
	unsigned long		nb_live;
	struct s_header		*next;
}						t_header;

typedef struct			s_process
{
	t_header			*champ;
	long				id;
	unsigned int		pc;
	unsigned int		carry;
	unsigned int		reg[REG_NUMBER];
	int					cooldown;
	unsigned long		last_live;
	int					inst;
	struct s_process	*next;
}						t_process;

typedef struct			s_opt
{
	char				*name;
	char				has_value;
	char				value_needed;
	char				store_value;
	char				value_can_be_negative;
}						t_opt;

typedef struct			s_option
{
	int					verbose;
	char				visu;
	long				dump;
}						t_option;

typedef struct			s_vm
{
	t_opt				*opt;
	t_option			*option;
	t_header			*champion;
	t_header			*ll_champ;
	t_process			*process;
	unsigned int		nb_player;
	unsigned char		memory[MEM_SIZE];
	long				c_todie;
	long				curr_c_todie;
	unsigned long		c_delta;
	unsigned long		nbr_live;
	unsigned long		old_nbr_live;
	unsigned long		max_check;
	unsigned long		check;
	unsigned long		cycle;
	unsigned long		nb_process;
	int					mem_mov;
}						t_vm;

/*
** Utility.c
*/

void					ft_exit(char *str);
void					*ft_memalloc_exit(size_t size);

#endif
