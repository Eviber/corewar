
#include <asm.h>
#include <corewar.h>

t_op *get_opt()
{
	static t_op    op_tab[17] = {
		{"live", 1, T_DIR , 0, 0, 1},
		{"ld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 2},
		{"st", 2, T_REG + (T_IND + T_REG) * 8, 1, 0, 3},
		{"add", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 4},
		{"sub", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0, 5},
		{"and", 3, T_REG + T_DIR + T_IND + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 6},
		{"or", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 7},
		{"xor", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0, 8},
		{"zjmp", 1, T_DIR, 0, 1, 9},
		{"ldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1, 10},
		{"sti", 3, T_REG + (T_REG + T_DIR + T_IND) * 8 + (T_DIR + T_REG) * 64, 1, 1, 11},
		{"fork", 1, T_DIR, 0, 1, 12},
		{"lld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 13},
		{"lldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1, 14},
		{"lfork", 1, T_DIR, 0, 1, 15},
		{"aff", 1, T_REG, 1, 0, 16},
		{0, 0, 0, 0, 0, 15} };

	return(op_tab);
}

void analyse_param(t_node *node) //
{
	int i;

	if (node->type == REG)
	{
		i = ft_atoi(node->name + 1);
		if (i > REG_NUMBER)
			ft_error(node->name + 1, 5, 0);
	}
	else if (node->type == DIRECT)
	{
		i = ft_atoi(node->name + 1);
	}
	else if (node->type == IND)
	{
		i = ft_atoi(node->name);
	}
}

void get_param(t_node *root, t_op *instruction)
{
	t_child *child;
	t_child *deep_child;
	int i;

	child = root->children->next;
	i = 1;
	while (child)
	{
		deep_child = child;
		while (deep_child->elem->type == PARAM)
			deep_child = deep_child->elem->children;
		if (deep_child->elem->type == REG && instruction->type & T_REG * i)
			analyse_param(deep_child->elem);
		else if (deep_child->elem->type == DIRECT && instruction->type & T_DIR * i)
			analyse_param(deep_child->elem);
		else if (deep_child->elem->type == IND && instruction->type & T_IND * i)
			analyse_param(deep_child->elem);
		else
			ft_error(deep_child->elem->name, 8, deep_child->elem->type);
		child = child->next;
		i *= 8;
	}
}

void search_inst(t_node *root, t_op *instruction)
{
	t_child *child;
	int i;

  if (root->type != INST)
  {
    child = root->children;
    while (child)
    {
      search_inst(child->elem, instruction);
      child = child->next;
    }
  }
  else
  {
		i = -1;
		while (++i < 16 && ft_strcmp(root->children->elem->name, instruction[i].name))
			;
		if (i < 16)
			get_param(root, &instruction[i]);
		else
			ft_error(root->children->elem->name, 7, root->type);
  }
}

void check_fct_params(t_node *root)
{
	t_op *instruction;
	t_node *tmp_tree;

	instruction = get_opt();
	tmp_tree = root;
	search_inst(root, instruction);
}
