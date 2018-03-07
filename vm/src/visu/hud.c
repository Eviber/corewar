/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:37:09 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/07 09:43:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include "visu.h"

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

static SDL_Rect		hudputstr(t_winenv *env, char *str, SDL_Rect dst)
{
	SDL_Texture	*tex;

	tex = strtotex(str, env, (SDL_Color){255, 255, 255, 255});
	free(str);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	dst.x = (env->hudrect.w - dst.w) / 2;
	SDL_RenderCopy(env->render, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
	dst.y += dst.h * 2;
	return (dst);
}

void				huddisp(t_winenv *env)
{
	SDL_Rect	dst;
	char		*str;

	env->cps = (env->cps + 1000 / (env->ticks - env->lastticks + !(env->ticks - env->lastticks))) / 2;
	dst.y = env->hudrect.w / 10;
	cleartex(env->render, env->hudtex,  env->palette[0]);
	ft_asprintf(&str, "Cycle :         %14lu%c", env->vm->cycle, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Processes :     %14lu%c", env->vm->nb_process, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Cycles to die : %9lu/%lu%c", env->vm->curr_c_todie, env->vm->c_todie, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Cycle delta :   %14lu%c", env->vm->c_delta, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "NBR_LIVE :      %11lu/%lu%c", env->vm->nbr_live - env->vm->old_nbr_live, NBR_LIVE, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Checks :        %11lu/%lu%c", env->vm->check, MAX_CHECKS, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "CPS :           %14lu%c", env->cps, 0);
	dst = hudputstr(env, str, dst);
}

