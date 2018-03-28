/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:58:13 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/28 12:15:29 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	clean_env(t_env *env, int option)
{
	if (env->name)
		ft_memdel((void **)&env->name);
	ft_memdel((void **)&env->res);
	ft_memdel((void **)&env->champ);
	env->line = 0;
	env->state = 0;
	env->error = 0;
	if (option == 2)
	{
		ft_memdel((void **)&env->op);
		ft_memdel((void **)&env);
	}
}

void	ft_other_error(t_env *env, char *name, int error)
{
	if (error == 7)
		ft_dprintf(2, "Invalid instruction at token \
[TOKEN][%03d:%03d] INSTRUCTION ""%s""\n",\
				env->line, env->index, name);
	if (error == 8)
		ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
	if (error == 9)
		ft_dprintf(2, "No such label %s while attempting to dereference \
token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
	if (error == 10)
		ft_dprintf(2, "Error all the attribut are not present.\n");
	if (error == 11)
		ft_dprintf(2, "This is champ has no named, I didn't like this \
type of bad guys\n");
	if (error == 12)
		ft_dprintf(2, "Serisouly, a champ without comment, where the \
punch line of %s\n", env->name);
	if (error == 13)
		ft_dprintf(2, "This is just a weak champ without any line of code\n");
	if (error == 14)
		ft_dprintf(2, "Extension of %s is invalid\n", name);
	if (error == 15)
		ft_dprintf(2, "Less argument in %s at line %d than needed\n",
				name, env->line);
}

void	ft_error(t_env *env, char *name, int error)
{
	ft_dprintf(2, "Compiling of %s fail : ", (env->name) ? env->name : name);
	env->error = 1;
	if (error > 6)
		ft_other_error(env, name, error);
	if (error == 1)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
	if (error == 2)
		ft_dprintf(2, "Name too long (Max length %d)\n", PROG_NAME_LENGTH);
	if (error == 3)
		ft_dprintf(2, "Comment too long (Max length %d)\n", COMMENT_LENGTH);
	if (error == 4)
		ft_dprintf(2, "Invalid instruction at token \
[TOKEN][%03d:%03d] PARAMETER ""%s""\n",\
				env->line, env->index, name);
	if (error == 5)
		ft_dprintf(2, "Number of register %s\
				greater than %d\n", name, REG_NUMBER);
	if (error == 6)
		ft_dprintf(2, "More argument in %s at line %d \
than allowd\n", name, env->line);
}
