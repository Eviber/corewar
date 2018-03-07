/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:37:09 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/07 17:45:59 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>

#include "corewar.h"
#include "visu.h"

static SDL_Rect		hudputstr(t_winenv *env, char *str, SDL_Rect dst)
{
	SDL_Texture	*tex;

	tex = strtotex(str, env, (SDL_Color){255, 255, 255, 255});
	free(str);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	dst.x = (env->hudrect.w - dst.w) / 2;
	SDL_RenderCopy(env->render, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
	dst.y += dst.h;
	return (dst);
}

/*
typedef struct			s_vm
{
	unsigned int		nb_player;
	long				c_todie;
	long				curr_c_todie;
	unsigned long		c_delta;
	unsigned long		nbr_live;
	unsigned long		max_check;
	unsigned long		check;
	unsigned long		cycle;
	unsigned long		nb_process;
	int					mem_mov;
}						t_vm;
*/

static void			hudvm(t_winenv *env, t_vm *vm)
{
	SDL_Rect	dst;
	char		*str;
	char		*tmp;

	env->cps = (env->cps + 1000 / (env->ticks - env->lastticks + !(env->ticks - env->lastticks))) / 2;
	dst.y = env->hudrect.w / 10;
	ft_asprintf(&str, "Cycle :         %14lu%c", vm->cycle, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Processes :     %14lu%c", vm->nb_process, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&tmp, "%lu/%lu%c", vm->curr_c_todie, vm->c_todie, 0);
	ft_asprintf(&str, "Cycles to die : %14s%c", tmp, 0);
	free(tmp);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Cycle delta :   %14lu%c", vm->c_delta, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "NBR_LIVE :      %11lu/%lu%c", vm->nbr_live - vm->old_nbr_live, NBR_LIVE, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Checks :        %11lu/%lu%c", vm->check, MAX_CHECKS, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "CPS :           %14lu%c", env->cps, 0);
	dst = hudputstr(env, str, dst);
}

/*
typedef struct			s_header
{
	int					num;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned long		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned long		last_live;
	unsigned long		nb_live;
	struct s_header		*next;
}						t_header;
*/
static void			hudchamp(t_winenv *env, t_vm *vm, t_header *champ, int i)
{
	SDL_Rect	dst;
	char		*str;
	char		*tmp;

	dst.y = env->hudrect.w / 10 + env->hudrect.h * i / 5;
	dst.y = env->hudrect.h + env->charrect.h - (4 - i) * (env->charrect.h * 7 + env->hudrect.w / 20);
	ft_asprintf(&str, "Champion %d : %16s%c", champ->num, champ->prog_name, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Size : %22lu%c", champ->prog_size, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&tmp, "%lu (%lu)%c", vm->cycle - champ->last_live, champ->last_live, 0);
	ft_asprintf(&str, "Last live : %17s%c", tmp, 0);
	free(tmp);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Lives : %21lu%c", champ->nb_live_p, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "#############################%c", 0);
	dst = hudputstr(env, str, dst);
}

void				putrect(t_winenv *env)
{
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(env->render, 50, 50, 50, 255);
	rect.w = env->hudrect.w - env->hudrect.w / 10;
	rect.h = (env->hudrect.h - env->hudrect.w * 5 / 10) / 5;
	rect.x = env->hudrect.w / 20;
	rect.y = env->hudrect.w / 20;
	SDL_RenderFillRect(env->render, &rect);
	rect.h = env->charrect.h * 7;
	rect.y = env->hudrect.h - 4 * (rect.h + rect.x);
	SDL_SetRenderDrawColor(env->render, 60, 60, 60, 255);
	SDL_RenderFillRect(env->render, &rect);
	rect.y = env->hudrect.h - 3 * (rect.h + rect.x);
	SDL_SetRenderDrawColor(env->render, 70, 70, 70, 255);
	SDL_RenderFillRect(env->render, &rect);
	rect.y = env->hudrect.h - 2 * (rect.h + rect.x);
	SDL_SetRenderDrawColor(env->render, 80, 80, 80, 255);
	SDL_RenderFillRect(env->render, &rect);
	rect.y = env->hudrect.h - 1 * (rect.h + rect.x);
	SDL_SetRenderDrawColor(env->render, 90, 90, 90, 255);
	SDL_RenderFillRect(env->render, &rect);
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
