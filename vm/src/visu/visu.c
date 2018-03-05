/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:22:52 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/05 19:45:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "libft.h"

#include "corewar.h"
#include "visu.h"

////////////////////////////////////////////////////////////////////////////////

void				dispmemline(t_winenv *env, int line)
{
	SDL_Texture		*tex;
	SDL_Rect		dst;
	int				i;
	int				wunit;

	i = 0;
	SDL_QueryTexture(env->memtex, NULL, NULL, &wunit, NULL);
	dst.y = env->dispmode.h * line / 64;
	dst.h = env->dispmode.h / 64;
	while (i < 64)
	{
		dst.x = wunit * i / 64;
		tex = env->bytetex[(int)env->colormap[line * 64 + i]][env->vm->memory[line * 64 + i]];
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(env->render, tex, NULL, &dst);
		i++;
	}
}

void				dispproc(t_winenv *env)
{
	SDL_Rect	rect;
	SDL_Rect	memrect;
	t_process	*cur;

	SDL_QueryTexture(env->memtex, NULL, NULL, &memrect.w, &memrect.h);
	rect.w = memrect.w / 64;
	rect.h = memrect.h / 64;
	cur = env->vm->process;
	while (cur)
	{
		rect.x = (cur->pc % 64) * memrect.w / 64;
		rect.y = cur->pc / 64 * memrect.h / 64;
		if (cur->champ == env->vm->champion)
			SDL_SetRenderDrawColor(env->render, 50, 100, 50, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(env->render, 50, 50, 100, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(env->render, &rect);
		cur = cur->next;
	}
}

void				memdisp(t_winenv *env)
{
	int				i;

	i = 0;
	SDL_SetRenderDrawColor(env->render, 10, 10, 10, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->memtex);
	dispproc(env);
	while (i < MEM_SIZE / 64)
	{
		dispmemline(env, i);
		i++;
	}
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

typedef struct			s_process
{
	t_header			*champ;
	unsigned int		pc;
	unsigned int		carry;
	unsigned int		reg[REG_NUMBER];
	int					cooldown;
	unsigned long		last_live;
	int					inst;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	long				dump;
	t_header			*champion;
	t_header			*ll_champ;
	t_process			*process;
	unsigned int		nb_player;
	unsigned char		memory[MEM_SIZE];
	long				c_todie;
	unsigned long		c_delta;
	unsigned long		nbr_live;
	unsigned long		max_check;
	unsigned long		check;
	unsigned long		cycle;
	unsigned long		nb_process;
}						t_vm;
*/

SDL_Rect			hudputstr(t_winenv *env, char *str, SDL_Rect dst)
{
	SDL_Texture	*tex;

	tex = strtotex(str, env, (SDL_Color){255, 255, 255, 255});
	free(str);
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
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
	dst = (SDL_Rect){0,0,0,0};
	SDL_SetRenderDrawColor(env->render, 10, 10, 90, SDL_ALPHA_OPAQUE);
	cleartex(env->render, env->hudtex);
	ft_asprintf(&str, "Cycle : %lu%c", env->vm->cycle, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "Processes : %lu%c", env->vm->nb_process, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "CYCLE_TO_DIE : %lu%c", env->vm->c_todie, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "CYCLE_DELTA : %lu%c", env->vm->c_delta, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "NBR_LIVE : %lu%c", NBR_LIVE, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "MAX_CHECKS : %lu%c", MAX_CHECKS, 0);
	dst = hudputstr(env, str, dst);
	ft_asprintf(&str, "CPS : %4lu%c", env->cps, 0);
	dst = hudputstr(env, str, dst);
}

void				events(t_winenv *env)
{
	(void)env;
}

////////////////////////////////////////////////////////////////////////////////

void				putinvisu(unsigned int addr, t_header *champ)
{
	t_winenv		*env;
	t_header		*cur;
	int				i;

	env = getsdlenv(NULL);
	cur = env->vm->champion;
	i = 1;
	while (cur && cur != champ)
	{
		cur = cur->next;
		i++;
	}
	env->colormap[addr % MEM_SIZE] = i;
	env->colormap[addr + 1 % MEM_SIZE] = i;
	env->colormap[addr + 2 % MEM_SIZE] = i;
	env->colormap[addr + 3 % MEM_SIZE] = i;
}

int					visu(void)
{
	t_winenv		*env;

	env = getsdlenv(NULL);
	env->lastticks = env->ticks;
	env->ticks = SDL_GetTicks();
	if (env->vm->mem_mov)
		memdisp(env);
	huddisp(env);
	SDL_RenderPresent(env->render);
	while (!(env->quit |= SDL_QuitRequested()) && SDL_GetTicks() < env->ticks + 0)
	{}
		events(env);
		visu_update(env);
		SDL_RenderPresent(env->render);
	//}
	return (quitvisu(env));
}
