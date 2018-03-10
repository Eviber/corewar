/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visutools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:03:43 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/06 16:05:36 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_ttf.h>

#include "visu.h"

void				visu_update(t_winenv *env)
{
	SDL_SetRenderTarget(env->render, env->wintex);
	SDL_RenderCopy(env->render, env->memtex, NULL, &env->memrect);
	SDL_RenderCopy(env->render, env->hudtex, NULL, &env->hudrect);
	SDL_SetRenderTarget(env->render, NULL);
	SDL_RenderCopy(env->render, env->wintex, NULL, NULL);
}

SDL_Texture			*valtotex(t_winenv *env, int val, int base, SDL_Color color)
{
	const char		*digits;
	char			str[3];

	digits = "0123456789abcdef";
	str[0] = digits[val / base];
	str[1] = digits[val % base];
	str[2] = '\0';
	return (strtotex(str, env, color));
}

int					quitvisu(t_winenv *env)
{
	if (!env || env->quit || SDL_QuitRequested())
	{
		SDL_Quit();
		return (0);
	}
	return (1);
}
