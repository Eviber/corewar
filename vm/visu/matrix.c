/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:25:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/24 15:17:43 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>

#include "corewar.h"
#include "visu.h"

static void			dispmemline(t_winenv *env, int line)
{
	SDL_Texture		*tex;
	SDL_Rect		dst;
	int				i;
	int				wunit;

	i = 0;
	SDL_QueryTexture(env->memtex, NULL, NULL, &wunit, NULL);
	dst.y = env->dispmode.h * line / 64;
	dst.h = env->dispmode.h / 64;
	while (i < 64)
	{
		dst.x = wunit * i / 64;
		tex = env->bytetex[(int)env->colormap[line * 64 + i]]
							[env->vm->memory[line * 64 + i]];
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(env->render, tex, NULL, &dst);
		i++;
	}
}

static void			dispproc(t_winenv *env)
{
	SDL_Rect	rect;
	SDL_Rect	memrect;
	t_process	*cur;
	SDL_Color	color;

	SDL_QueryTexture(env->memtex, NULL, NULL, &memrect.w, &memrect.h);
	rect.h = memrect.h / 64;
	SDL_QueryTexture(env->bytetex[0][0], NULL, NULL, &rect.w, NULL);
	cur = env->vm->process;
	while (cur)
	{
		rect.x = (cur->pc % 64) * memrect.w / 64;
		rect.y = cur->pc / 64 * memrect.h / 64;
		color = env->proc_palette[cur->champ->index_color];
		SDL_SetRenderDrawColor(env->render, color.r, color.g, color.b, 0);
		SDL_RenderFillRect(env->render, &rect);
		cur = cur->next;
	}
}

void				memdisp(t_winenv *env)
{
	int				i;

	i = 0;
	cleartex(env->render, env->memtex, (SDL_Color){10, 10, 10, 255});
	dispproc(env);
	while (i < MEM_SIZE / 64)
	{
		dispmemline(env, i);
		i++;
	}
}
