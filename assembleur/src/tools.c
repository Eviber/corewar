/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:15:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void ft_error(t_env *env, char *name, int error)
{
	ft_dprintf(2, "Compiling of %s fail : ", env->name);
	if (error == 1)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
	if (error == 2)
		ft_dprintf(2, "Name too long (Max length %d)\n", PROG_NAME_LENGTH);
	if (error == 3)
		ft_dprintf(2, "Comment too long (Max length %d)\n",  COMMENT_LENGTH);
	if (error == 4)
		ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] PARAMETER ""%s""\n", env->line,  env->index, name);
	if (error == 5)
		ft_dprintf(2, "Number of register %s greater than %d\n", name, REG_NUMBER);
	if (error == 6)
		ft_dprintf(2, "More argument in %s at line %d than allow\n", name, env->line);
	if (error == 7)
		ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] INSTRUCTION ""%s""\n", env->line,  env->index, name);
	if (error == 8)
		ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
	if (error == 9)
		ft_dprintf(2, "No such label %s while attempting to dereference token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
	if (error == 10)
		ft_dprintf(2, "Error all the attribut are not present.\n");
	env->error = 1;
}

void load_new_roquet(t_label *target, t_env *env, int size)
{
	t_roquet *tmp;
	t_roquet *new_roquet;

	tmp = target->appel;
	new_roquet = ft_memalloc_exit(sizeof(t_roquet));
	new_roquet->value = env->pos_last_inst;
	new_roquet->pos = env->pos;
	new_roquet->i = env->index;
	new_roquet->j = env->line;
	new_roquet->size_max = size;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new_roquet;
	else
		target->appel = new_roquet;
}

void fill_memory(char *mem, long value, int size, int start)
{
	while (value && size--)
	{
		mem[start + size] =(char)value % 256;
		value = (value - (value % 256)) / 256;
	}
}

void *ft_memalloc_exit(size_t size)
{
	void *mem;
	if (!(mem = ft_memalloc(size)))
	{
		ft_dprintf(2, "Malloc has failed in this execution\n");
		exit(1);
	}
	return(mem);
}

void memory_manager(t_env *env, int size)
{
	char *save;
	long cmp;

	if (env->pos + size > CHAMP_MAX_SIZE)
		env->error = 2;
	else if (env->pos + size > env->size_champ)
	{
		cmp = -1;
		save = env->champ;
		env->champ = ft_memalloc_exit(env->pos + 40);
		while(++cmp < env->size_champ)
			env->champ[cmp] = save[cmp];
		ft_memdel((void**)&save);
		env->size_champ = env->pos + 40;
	}
}
