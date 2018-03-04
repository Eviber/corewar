/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/03 12:13:30 by ygaude           ###   ########.fr       */
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
	SDL_DisplayMode		dispmode;
	SDL_Window			*win;
	SDL_Renderer		*render;
	TTF_Font			*font;
	SDL_Texture			*wintex;
	SDL_Texture			*memtex;
	SDL_Texture			*hudtex;
	t_vm				*vm;
	SDL_Texture			*bytetex[256];
	Uint32				lastticks;
	Uint32				ticks;
	int					quit;
	unsigned int		cps;
}						t_winenv;

void					visu_init(t_vm *vm);
int						visu(void);

#endif
