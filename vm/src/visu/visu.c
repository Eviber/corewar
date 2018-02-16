/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:22:52 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/16 03:10:43 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "visu.h"

void				panic(const char *str, const char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	exit(SDL_EXIT_ERROR);
}

t_winenv			*getsdlenv(t_vm *vm)
{
	static t_winenv	*winenv = NULL;

	if (!winenv && vm)
		if ((winenv = (t_winenv *)ft_memalloc(sizeof(t_winenv))))
			winenv->vm = vm;
	return (winenv);
}

void				visu_initenv(t_vm *vm)
{
	t_winenv		*env;
	t_pos			min;
	t_pos			max;
	int				i;

	env = getsdlenv(vm);
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		panic("Error while initializing SDL: ", SDL_GetError());
	if (SDL_GetDesktopDisplayMode(0, &(env->dispmode)))
		panic("SDL_GetDesktopDisplayMode failed: ", SDL_GetError());
	env->win = SDL_CreateWindow("Corewar",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				env->dispmode.w, env->dispmode.h, 0);
	if (!env->win)
		panic("Error while creating window: ", SDL_GetError());
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
		panic("Error while creating renderer: ", SDL_GetError());
	if (TTF_Init() == -1 || !(env->font = TTF_OpenFont("joystix.ttf", 48)))
		panic("Error while initializing SDL_TTF: ", TTF_GetError());
	SDL_SetRenderDrawColor(env->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env->render);
}

void				visu_init(t_vm *vm)
{
	visu_initenv(vm);
}

int					quitvisu(t_winenv *env, int quit)
{
	if (!env || quit)
	{
		SDL_Quit();
		return (0);
	}
	return (1);
}

int					visu(void)
{
	t_winenv		*env;
	int				quit;

	env = getsdlenv(NULL);
	env->ticks = SDL_GetTicks();
	while (SDL_GetTicks() - env->ticks < TURNTIME + 100 && !SDL_QuitRequested())
	{
		if (env)
		{
			frameticks = SDL_GetTicks();
			SDL_SetRenderDrawColor(env->render, 0, 0, 0, 20);
			SDL_RenderClear(env->render);
			SDL_SetRenderDrawBlendMode(env->render, SDL_BLENDMODE_NONE);
			SDL_RenderPresent(env->render);
		}
	}
	if (!quit)
		updatelast(env, *(env->colony));
	return (quitvisu(env, quit));
}
