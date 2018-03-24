/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:39:28 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/23 10:39:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_rules	*get_rules(t_token type)  //mmethode rapide
{
	static t_rules	*rules[14] = {
	{ 0, {PROG, HEADER, CODE, 0, 0}},
	{ 1, {HEADER, CMD_NAME, CMD_CMT, 0, 0 } },
	{ 0, {HEADER, CMD_CMT, CMD_NAME, 0, 0 }},
	{ 1, {CODE, LINE, CODE, 0, 0 }},
	{ 0, {CODE, ENDCODE, 0, 0, 0 }},
	{ 2, {LINE, LABEL, 0, 0, 0 }},
	{ 1, {LINE, INST, 0, 0, 0 }},
	{ 0, {LINE, LABEL, INST, 0, 0 }},
	{ 0, {INST, FCT, PARAM, 0, 0 }},
	{ 3, {PARAM, PARAM, SEP, PARAM, 0 }},
	{ 2, {PARAM, REG, 0, 0, 0 }},
	{ 1, {PARAM, DIRECT, 0, 0, 0 }},
	{ 0, {PARAM, IND, 0, 0, 0 }},
	{ 0, { 0, 0, 0, 0, 0 }},
	};
	int i;

	i = 0;
	while (rules[i].res[0] && rules[i].res[0] != type)
		i++;
	return (rules[i]);
}

void check_grammar(t_node *root, t_rules rules, int deep, t_child *tmp_child)
{
	int i;

	i = 0;
	if (root->type == rules.res[i])
	{
		ft_printf("Analyse type : ");
		print_token(root->type, deep);
		while (tmp_child->children)
		{
			print_token(tmp_child->elem->type, deep + 2);
			if (tmp_child->elem->type != rules.res[++i])
				pexit("Tree error", -4);
			if (tmp_child->elem->type > NONE && tmp_child->elem->type <= PARAM)
				check_grammar(tmp_child->elem, get_rules(tmp_child->elem->type), deep + 4, root->children->next);
			tmp_child = tmp_child->next;
		}
	}
	else if (rules.possibility == 0)
		pexit("Tree error", -4);
	else
		check_grammar(root, *((&rules) + 1), deep);
}

void parser(t_node *root)
{
	t_node *tmp_tree;

	tmp_tree = root;
  check_grammar(tmp_tree, get_rules(root->type), 0, tmp_tree->child);
  //reduce_tree(root);
  //check_fct_params(root);
  //translate(root);
}
