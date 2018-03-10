/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:27:56 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/07 15:36:54 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "corewar.h"
#include "visu.h"

static void		event_pause(SDL_Event *event, int *mod, t_winenv *env)
{
	while (!(env->quit |= SDL_QuitRequested()))
	{
		if (SDL_PollEvent(event) && \
		(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP))
		{
			if (event->key.keysym.scancode == SDL_SCANCODE_SPACE && \
			event->key.state == SDL_PRESSED)
			{
				*mod = (*mod ^ (*mod & EVENT_STOP));
				if ((*mod & EVENT_STEP))
					*mod ^= EVENT_STEP;
				return ;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_S && \
			event->key.state == SDL_PRESSED)
			{
				*mod |= EVENT_STEP;
				*mod = (*mod ^ (*mod & EVENT_STOP));
				return ;
			}
		}
	}
}

static void		event_step(SDL_Event *event, int *mod, t_winenv *env)
{
	while (!(env->quit |= SDL_QuitRequested()))
	{
		if (SDL_PollEvent(event) && \
		(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP))
		{
			if (event->key.keysym.scancode == SDL_SCANCODE_SPACE && \
			event->key.state == SDL_PRESSED)
			{
				*mod = (*mod ^ (*mod & EVENT_STOP));
				if ((*mod & EVENT_STEP))
					*mod ^= EVENT_STEP;
				return ;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_S && \
			event->key.state == SDL_PRESSED)
				return ;
		}
	}
}

void			event_manager(t_winenv *env)
{
	static int			mod = EVENT_STOP;
	SDL_Event			event;

	while (SDL_PollEvent(&event) && !(env->quit |= SDL_QuitRequested()))
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				if (event.key.state == SDL_PRESSED)
					mod |= EVENT_STOP_P;
				else if ((mod & EVENT_STOP_P))
					mod |= EVENT_STOP_R;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S)
			{
				if (event.key.state == SDL_PRESSED)
					mod |= EVENT_STEP;
			}
		}
	if ((mod & EVENT_STEP))
		event_step(&event, &mod, env);
	if ((mod & EVENT_STOP) == EVENT_STOP)
		event_pause(&event, &mod, env);
}
