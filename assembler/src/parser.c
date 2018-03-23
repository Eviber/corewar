/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 05:48:28 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/16 20:24:04 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_rules	*get_rules(void)
{
	static t_rules	rules[] = {
	{ PROG, { HEADER, CODE, 0, 0 } },
	{ HEADER, { CMD_NAME, CMD_CMT, 0, 0 } },
	{ HEADER, { CMD_CMT, CMD_NAME, 0, 0 } },
	{ CODE, { LINE, CODE, 0, 0 } },
	{ CODE, { ENDCODE, 0, 0, 0 } },
	{ LINE, { LABEL, 0, 0, 0 } },
	{ LINE, { INST, 0, 0, 0 } },
	{ LINE, { LABEL, INST, 0, 0 } },
	{ PARAM, { PARAM, SEP, PARAM, 0 } },
	{ PARAM, { REG, 0, 0, 0 } },
	{ PARAM, { DIRECT, 0, 0, 0 } },
	{ PARAM, { IND, 0, 0, 0 } },
	{ 0, { 0, 0, 0, 0 } },
	};

	return (rules);
}

#include <asm.h>

void check_grammar(t_node *root)
{
  t_rules *rule;
  t_node *tmp_tree;
  int i;

  tmp_tree = root;
  rule = get_rules();
}

void parser(t_node *root)
{
  check_grammar(root);
  reduce_tree(root);
  check_fct_params(root);
  translate(root);
}
