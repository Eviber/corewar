/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:37:09 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/25 15:10:41 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>

#include "corewar.h"
#include "visu.h"

static SDL_Rect		hudputstr(t_winenv *env, char *str, SDL_Rect dst,
					SDL_Color color)
{
	SDL_Texture	*tex;

	tex = strtotex(str, env, color);
	free(str);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	dst.x = (env->hudrect.w - dst.w) / 2;
	SDL_RenderCopy(env->render, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
	dst.y += dst.h;
	return (dst);
}

static void			hudvm(t_winenv *env, t_vm *vm)
{
	SDL_Rect	dst;
	char		*str;
	char		*tmp;

	env->cps = 1000 /
				(env->ticks - env->lastticks + !(env->ticks - env->lastticks));
	dst.y = env->hudrect.w / 10;
	ft_asprintf(&str, "Cycle :         %14lu", vm->cycle);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&str, "Processes :     %14lu", vm->nb_process);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&tmp, "%lu/%lu", vm->curr_c_todie, vm->c_todie);
	ft_asprintf(&str, "Cycles to die : %14s", tmp);
	free(tmp);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&str, "Cycle delta :   %14lu", vm->c_delta);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&str, "NBR_LIVE :      %11lu/%lu", vm->nbr_live - \
	vm->old_nbr_live, NBR_LIVE);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&str, "Checks :        %11lu/%lu", MAX_CHECKS - \
	vm->max_check, MAX_CHECKS);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
	ft_asprintf(&str, "CPS :           %14lu", env->cps);
	dst = hudputstr(env, str, dst, (SDL_Color){255, 255, 255, 255});
}

static void			hudchamp(t_winenv *env, t_vm *vm, t_header *champ, int i)
{
	SDL_Rect	dst;
	char		*str;
	char		*tmp;

	dst.y = env->hudrect.w / 10 + env->hudrect.h * i / 5;
	dst.y = env->hudrect.h + env->charrect.h - (4 - i) * \
	(env->charrect.h * 7 + env->hudrect.w / 20);
	ft_asprintf(&str, "Champion %d : %16s", champ->num, champ->prog_name);
	dst = hudputstr(env, str, dst, env->proc_palette[champ->index_color]);
	ft_asprintf(&str, "Size : %22lu", champ->prog_size);
	dst = hudputstr(env, str, dst, env->proc_palette[champ->index_color]);
	ft_asprintf(&tmp, "%lu (%lu)", vm->cycle - \
	champ->last_live, champ->last_live);
	ft_asprintf(&str, "Last live : %17s", tmp);
	free(tmp);
	dst = hudputstr(env, str, dst, env->proc_palette[champ->index_color]);
	ft_asprintf(&str, "Lives : %21lu", champ->nb_live_p);
	dst = hudputstr(env, str, dst, env->proc_palette[champ->index_color]);
	ft_asprintf(&str, "Processes : %17lu", champ->nb_process);
	dst = hudputstr(env, str, dst, env->proc_palette[champ->index_color]);
}

void				putrect(t_winenv *env)
{
	SDL_Rect		rect;
	unsigned int	i;

	SDL_SetRenderDrawColor(env->render, 50, 50, 50, 255);
	rect.w = env->hudrect.w - env->hudrect.w / 10;
	rect.h = (env->hudrect.h - env->hudrect.w * 5 / 10) / 5;
	rect.x = env->hudrect.w / 20;
	rect.y = env->hudrect.w / 20;
	SDL_RenderFillRect(env->render, &rect);
	rect.h = env->charrect.h * 7;
	i = 0;
	while (i < env->vm->nb_player)
	{
		rect.y = env->hudrect.h - (4 - i) * (rect.h + rect.x);
		SDL_SetRenderDrawColor(env->render, 60 + 10 * i,
											60 + 10 * i,
											60 + 10 * i, 255);
		SDL_RenderFillRect(env->render, &rect);
		i++;
	}
}

void				huddisp(t_winenv *env)
{
	t_header	*cur;
	int			i;

	i = 0;
	cur = env->vm->champion;
	cleartex(env->render, env->hudtex, env->palette[0]);
	putrect(env);
	hudvm(env, env->vm);
	while (cur)
	{
		hudchamp(env, env->vm, cur, i);
		cur = cur->next;
		i++;
	}
}
