/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdltools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 08:42:23 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/06 08:22:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_ttf.h>
#include "libft.h"

#include "corewar.h"
#include "visu.h"

void			panic(const char *str, const char *str2)
{
	ft_dprintf(2, "%s: %s\n", str, str2);
	exit(-1);
}

t_winenv		*getsdlenv(t_vm *vm)
{
	static t_winenv	*winenv = NULL;

	if (!winenv && vm)
		if ((winenv = (t_winenv *)ft_memalloc(sizeof(t_winenv))))
		{
			winenv->vm = vm;
			winenv->quit = 0;
		}
	return (winenv);
}

SDL_Texture		*getnewtex(t_winenv *env, int access, int w, int h)
{
	SDL_Texture		*tex;

	tex = SDL_CreateTexture(env->render, env->dispmode.format, access, w, h);
	if (!tex)
		panic("Failed creating texture", SDL_GetError());
	return (tex);
}

void			cleartex(SDL_Renderer *render, SDL_Texture *tex, SDL_Color col)
{
	SDL_SetRenderDrawColor(render, col.r, col.g, col.b, col.a);
	SDL_SetRenderTarget(render, tex);
	SDL_RenderClear(render);
}

SDL_Texture		*strtotex(char *str, t_winenv *env, SDL_Color color)
{
	SDL_Texture		*tex;
	SDL_Surface		*surf;

	surf = TTF_RenderText_Blended(env->font, str, color);
	if (!surf)
		panic("Failed creating text surface", SDL_GetError());
	tex = SDL_CreateTextureFromSurface(env->render, surf);
	if (!tex)
		panic("Failed converting surface to texture", SDL_GetError());
	SDL_FreeSurface(surf);
	return (tex);
}
