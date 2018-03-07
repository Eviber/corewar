/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:22:52 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/07 15:58:34 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "libft.h"

#include "corewar.h"
#include "visu.h"

void				events(t_winenv *env)
{
	(void)env;
}

void				putinvisu(unsigned int addr, t_header *champ)
{
	t_winenv		*env;
	t_header		*cur;
	int				i;

	env = getsdlenv(NULL);
	cur = env->vm->champion;
	i = 1;
	while (cur && cur != champ)
	{
		cur = cur->next;
		i++;
	}
	env->colormap[(addr + 0) % MEM_SIZE] = i;
	env->colormap[(addr + 1) % MEM_SIZE] = i;
	env->colormap[(addr + 2) % MEM_SIZE] = i;
	env->colormap[(addr + 3) % MEM_SIZE] = i;
}

int					visu(void)
{
	t_winenv		*env;

	env = getsdlenv(NULL);
	env->lastticks = env->ticks;
	env->ticks = SDL_GetTicks();
	if (env->vm->mem_mov)
		memdisp(env);
	huddisp(env);
	SDL_RenderPresent(env->render);
	while (!(env->quit |= SDL_QuitRequested()) && SDL_GetTicks() < env->ticks + 0)
	{}
		events(env);
		visu_update(env);
		SDL_RenderPresent(env->render);
	//}
	return (quitvisu(env));
}
