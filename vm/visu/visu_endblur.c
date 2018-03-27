/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_endblur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:02:50 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/27 18:05:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "visu.h"

static void	update_blur(t_winenv *env, SDL_Rect rect)
{
	SDL_RenderClear(env->render);
	SDL_SetRenderTarget(env->render, env->wintex);
	SDL_RenderFillRect(env->render, &rect);
	SDL_SetRenderTarget(env->render, NULL);
	SDL_RenderCopy(env->render, env->wintex, NULL, NULL);
	SDL_RenderPresent(env->render);
}

void		end_blur(t_winenv *env, int squares[45][80], SDL_Color color)
{
	SDL_Rect	rect;
	int			i;
	int			j;

	rect = (SDL_Rect){0, 0, 32, 32};
	rect.x = rand() % 80 * 32;
	rect.y = rand() % 45 * 32;
	i = 0;
	while (i < 45 * 80 && !(j = 0))
	{
		while ((i < 45 * 80) && j < 100)
		{
			while (squares[rect.y / 32][rect.x / 32])
			{
				if ((env->quit |= SDL_QuitRequested()))
					return ;
				rect.x = rand() % 80 * 32;
				rect.y = rand() % 45 * 32;
			}
			setcolor(env->render, color, 50 + (i++ / 100) * 2);
			update_blur(env, rect);
			squares[rect.y / 32][rect.x / 32] = 1;
		}
	}
	SDL_RenderPresent(env->render);
}
