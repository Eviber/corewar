/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/27 18:03:27 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL_ttf.h>

# include "corewar.h"

# define TEXTARGET SDL_TEXTUREACCESS_TARGET
# define EVENT_STEP 1
# define EVENT_STOP_P 2
# define EVENT_STOP_R 4
# define EVENT_STOP 6

typedef struct			s_winenv
{
	char				colormap[MEM_SIZE];
	SDL_Texture			*bytetex[MAX_PLAYERS + 1][256];
	SDL_Color			palette[MAX_PLAYERS + 1];
	SDL_Color			proc_palette[MAX_PLAYERS];
	SDL_DisplayMode		dispmode;
	SDL_Rect			winrect;
	SDL_Rect			memrect;
	SDL_Rect			hudrect;
	SDL_Rect			charrect;
	SDL_Window			*win;
	SDL_Renderer		*render;
	TTF_Font			*bigfont;
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

/*
**	Generic tools
*/
void					panic(const char *str, const char *str2);
t_winenv				*getsdlenv(t_vm *vm);
SDL_Texture				*getnewtex(t_winenv *env, int access, int w, int h);
void					cleartex(SDL_Renderer *render, SDL_Texture *tex,
									SDL_Color col);
SDL_Texture				*strtotex(char *str, t_winenv *env,
									SDL_Color color, int fat);
void					setcolor(SDL_Renderer *render, SDL_Color color,
									unsigned char alpha);

/*
**	Specific tools
*/
void					visu_update(t_winenv *env);
SDL_Texture				*valtotex(t_winenv *env, int val, int base,
									SDL_Color color);
int						quitvisu(t_winenv *env);
SDL_Color				hsl(int h, double s, double l);
void					event_manager(t_winenv *env);
void					end_blur(t_winenv *env, int squares[45][80],
									SDL_Color color);

/*
**	Subfunctions
*/
void					memdisp(t_winenv *env);
void					huddisp(t_winenv *env);

/*
**	Main functions
*/
void					visu_init(t_vm *vm);
void					visu_finish(t_header *winner);
int						visu(void);
void					putinvisu(unsigned int addr, t_header *champ);

#endif
