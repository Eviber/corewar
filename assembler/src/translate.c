#include <asm.h>
#include <corewar.h>
/*
void loop_translate(t_node *tree, int *i)
{
  t_child *child;
	int i;

  if (root)
  {
    child = root->children;
    while (child)
    {
      search_inst(child->elem, instruction);
      child = child->next;
    }
  }
  if (root && !root->children)
  {
    *i += 1;
  }
}
*/
void translate(t_node *tree, int size)
{
  size = 0;
  print_tree(tree);
}
