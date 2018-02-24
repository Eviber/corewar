/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 22:12:30 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/23 22:18:19 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(unsigned char peb, t_param *param)
{
	if (PARAM_ONE(peb) == REG_CODE && !(param->one <= 16 && param->one > 0))
		return (1);
	if (PARAM_TWO(peb) == REG_CODE && !(param->two <= 16 && param->two > 0))
		return (1);
	if (PARAM_THR(peb) == REG_CODE && !(param->thr <= 16 && param->thr > 0))
		return (1);
	return (0);
}
