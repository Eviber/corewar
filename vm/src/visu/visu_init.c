/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 08:36:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/05 22:18:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_ttf.h>

#include "corewar.h"
#include "visu.h"

static void			initsdl(t_winenv *env)
{
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		panic("Error while initializing SDL", SDL_GetError());
	if (SDL_GetDesktopDisplayMode(0, &(env->dispmode)))
		panic("SDL_GetDesktopDisplayMode failed", SDL_GetError());
	env->win = SDL_CreateWindow("Corewar",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				env->dispmode.w, env->dispmode.h, SDL_WINDOW_FULLSCREEN);
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
	unsigned int	i;
	unsigned int	j;

	env->bytetex[0][0] = valtotex(env, 0, 16, env->palette[0]);
	i = 1;
	while (i < MAX_PLAYERS + 1)
	{
		j = 0;
		while (j < 256)
		{
			env->bytetex[i][j] = valtotex(env, j, 16, env->palette[i]);
			j++;
		}
		i++;
	}
}

static void			loadpalette(t_winenv *env)
{
	unsigned int		i;
	int					step;

	step = 360 / ((env->vm->nb_player > 3) ? env->vm->nb_player + 1 : 3);
	env->palette[0] = hsl(0, 0, 10);
	i = 0;
	while (i < MAX_PLAYERS + 1)
	{
		env->palette[i + 1] = hsl(120 + i * step, 100, 60);
		i++;
	}
}

void				set_colormap(t_winenv *env)
{
	t_header		*cur;
	int				i;

	i = 0;
	cur = env->vm->champion;
	memset(env->colormap, 0, MEM_SIZE);
	while (cur)
	{
		memset(env->colormap + (i * MEM_SIZE / env->vm->nb_player), i + 1, cur->prog_size);
		i++;
		cur = cur->next;
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
	loadpalette(env);
	loadbytetex(env);
	set_colormap(env);
	SDL_SetRenderDrawColor(env->render, 100, 50, 50, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->wintex);
	SDL_SetRenderDrawColor(env->render, 50, 100, 50, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->memtex);
	SDL_SetRenderDrawColor(env->render, 50, 50, 100, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->hudtex);
	visu_update(env);
}
