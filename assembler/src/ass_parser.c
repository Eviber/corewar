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

static int search_rules(t_token type, t_rules *rules)
{
	int i;

	i = 0;
	while (i < 14 && rules[i].res[0] != type)
		i++;
	return (i);
}

static t_rules	*get_rules()
{
	static t_rules	rules[14] = {
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

	return (rules);
}

void check_grammar(t_node *root, t_rules *rules, int j)
{
	int i;
	t_child *child;

	child = root->children;
	i = search_rules(root->type, rules);
	while (child)
	{
		if (child->elem->type == rules[i].res[++j])
			child = child->next;
		else if (rules[i++].possibility && !(j = 0))
			child = root->children;
		else
			pexit("Error Token 1\n", -1);
	}
	if (rules[i].res[++j])
		pexit("Error Token 2\n", -1);
	else if ((child = root->children))
		while(child)
		{
			if (child->elem->type > NONE && child->elem->type <= PARAM)
				check_grammar(child->elem, rules, 0);
			child = child->next;
		}
}

void parser(t_node *root)
{
	t_node *tmp_tree;
	t_rules *rules;

	tmp_tree = root;
	rules = get_rules();
  check_grammar(tmp_tree, rules, 0);
  reduce_tree(root);
	tmp_tree = root,
  check_fct_params(tmp_tree);
  //translate(root);
}
