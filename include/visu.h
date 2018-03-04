/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/04 13:51:21 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL_ttf.h>

# include "corewar.h"

# define TEXTARGET SDL_TEXTUREACCESS_TARGET

typedef struct			s_winenv
{
	char				colormap[MEM_SIZE];
	SDL_Texture			*bytetex[MAX_PLAYERS + 1][256];
	SDL_Color			palette[MAX_PLAYERS + 1];
	SDL_DisplayMode		dispmode;
	SDL_Window			*win;
	SDL_Renderer		*render;
	TTF_Font			*font;
	SDL_Texture			*wintex;
	SDL_Texture			*memtex;
	SDL_Texture			*hudtex;
	t_vm				*vm;
	Uint32				lastticks;
	Uint32				ticks;
	int					quit;
	unsigned int		cps;
}						t_winenv;

SDL_Color				hsl(int h, double s, double l);
void					visu_init(t_vm *vm);
int						visu(void);

#endif
