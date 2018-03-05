/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:34:44 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/05 15:31:31 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

static int	tmptorgb(double tmp, double t1, double t2)
{
	double	res;

	if (6 * tmp < 1)
		res = t2 + (t1 - t2) * 6 * tmp;
	else if (2 * tmp < 1)
		res = t1;
	else if (3 * tmp < 2)
		res = t2 + (t1 - t2) * (2.0/3.0 - tmp) * 6;
	else
		res = t2;
	return ((int)lround(res * 255));
}

SDL_Color	hsl(int h, double s, double l)
{
	SDL_Color	res;
	double		t1;
	double		t2;

	h %= 360;
	s = s / 100.0;
	l = l / 100.0;
	t1 = (l < 0.5) ? l * (1 + s) : l + s - l * s;
	t2 = 2 * l - t1;
	res.a = 255;
	res.r = tmptorgb((double)((h + 120) % 360) / 360, t1, t2);
	res.g = tmptorgb((double)h / 360, t1, t2);
	res.b = tmptorgb((double)((h - 120 + 360) % 360) / 360, t1, t2);
	return (res);
}
