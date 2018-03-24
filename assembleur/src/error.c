/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:58:13 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/24 17:14:51 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_other_error(t_env *env, char *name, int error)
{
	if (error == 8)
		ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
	if (error == 9)
		ft_dprintf(2, "No such label %s while attempting to dereference\
				token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
	if (error == 10)
		ft_dprintf(2, "Error all the attribut are not present.\n");
	if (error == 11)
		ft_dprintf(2, "This is champ has no named, I didn't like this\
				type of bad guys\n");
	if (error == 12)
		ft_dprintf(2, "Serisouly, a champ without comment, where the\
				punch line of %s\n", env->name);
	if (error == 13)
		ft_dprintf(2, "This is just a weak champ without any line of code\n");
}

void	ft_error(t_env *env, char *name, int error)
{
	ft_dprintf(2, "Compiling of %s fail : ", env->name);
	if (error > 8)
		ft_other_error(env, name, error);
	if (error == 1)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
	if (error == 2)
		ft_dprintf(2, "Name too long (Max length %d)\n", PROG_NAME_LENGTH);
	if (error == 3)
		ft_dprintf(2, "Comment too long (Max length %d)\n", COMMENT_LENGTH);
	if (error == 4)
		ft_dprintf(2, "Invalid instruction at token\
				[TOKEN][%03d:%03d] PARAMETER ""%s""\n",\
				env->line, env->index, name);
	if (error == 5)
		ft_dprintf(2, "Number of register %s\
				greater than %d\n", name, REG_NUMBER);
	if (error == 6)
		ft_dprintf(2, "More argument in %s at line %d\
				than allow\n", name, env->line);
	if (error == 7)
		ft_dprintf(2, "Invalid instruction at token\
				[TOKEN][%03d:%03d] INSTRUCTION ""%s""\n",\
				env->line, env->index, name);
	env->error = 1;
}
