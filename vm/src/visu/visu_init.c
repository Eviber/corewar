/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 08:36:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/05 09:43:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_ttf.h>

#include "visu.h"

static void			initsdl(t_winenv *env)
{
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		panic("Error while initializing SDL", SDL_GetError());
	if (SDL_GetDesktopDisplayMode(0, &(env->dispmode)))
		panic("SDL_GetDesktopDisplayMode failed", SDL_GetError());
	env->win = SDL_CreateWindow("Corewar",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				env->dispmode.w, env->dispmode.h, 0);//SDL_WINDOW_FULLSCREEN);
	if (!env->win)
		panic("Error while creating window", SDL_GetError());
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
		panic("Error while creating renderer", SDL_GetError());
	if (TTF_Init() == -1 || !(env->font = TTF_OpenFont("roboto.ttf", 20)))
		panic("Error while initializing SDL_TTF", TTF_GetError());
	SDL_SetRenderDrawColor(env->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env->render);
}

static void			loadbytetex(t_winenv *env)
{
	int		i;

	i = 0;
	while (i < 256)
	{
		env->bytetex[0][i] = valtotex(env, i, 16);
		i++;
	}
}

void				visu_init(t_vm *vm)
{
	t_winenv		*env;
	SDL_DisplayMode	dm;

	env = getsdlenv(vm);
	initsdl(env);
	SDL_GetDesktopDisplayMode(0, &env->dispmode);
	dm = env->dispmode;
	env->wintex = getnewtex(env, TEXTARGET, dm.w, dm.h);
	env->memtex = getnewtex(env, TEXTARGET, dm.w * 4 / 5, dm.h);
	env->hudtex = getnewtex(env, TEXTARGET, dm.w * 1 / 5, dm.h);
	loadbytetex(env);
	SDL_SetRenderDrawColor(env->render, 100, 50, 50, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->wintex);
	SDL_SetRenderDrawColor(env->render, 50, 100, 50, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->memtex);
	SDL_SetRenderDrawColor(env->render, 50, 50, 100, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->hudtex);
	visu_update(env);
}
