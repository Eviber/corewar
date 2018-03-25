/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 22:12:30 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/26 15:33:51 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(unsigned char peb, int nb_param, t_param *param)
{
	if (nb_param > 0 && PARAM_ONE(peb) == REG_CODE && \
	!(param->one <= REG_NUMBER && param->one > 0))
		return (1);
	if (nb_param > 1 && PARAM_TWO(peb) == REG_CODE && \
	!(param->two <= REG_NUMBER && param->two > 0))
		return (1);
	if (nb_param > 2 && PARAM_THR(peb) == REG_CODE && \
	!(param->thr <= REG_NUMBER && param->thr > 0))
		return (1);
	return (0);
}
