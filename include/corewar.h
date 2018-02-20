/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/02/16 05:52:47 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct			s_vm
{
	unsigned char		memory[MEM_SIZE];
	unsigned long		c_todie;
	unsigned long		c_delta;
	unsigned long		nbr_live;
	unsigned long		max_check;
	unsigned long		check;
}						t_vm;

typedef struct			s_process
{
	unsigned int		pc;
	unsigned int		carry;
	unsigned int		reg[REG_NUMBER];
	unsigned int		cooldown;
}						t_process;
