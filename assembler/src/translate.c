#include <asm.h>
#include <corewar.h>

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

void translate(t_node *tree, int size)
{
  long magic;
  char *res;
  int i;

  i = -1;
  magic = COREWAR_EXEC_MAGIC;
  res = ft_memalloc_exit(size + sizeof(COREWAR_EXEC_MAGIC) + COMMENT_LENGTH + PROG_NAME_LENGTH + sizeof(CHAMP_MAX_SIZE));
  while(++i < sizeof(COREWAR_EXEC_MAGIC))
  {

  }
  loop_translate(tree, &i)
}
