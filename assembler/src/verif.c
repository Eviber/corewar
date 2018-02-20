#include <stdio.h>

void print(char *name, int type, long pos, int space)
{
  while (--space > 0)
  {
    if (space % 4)
      printf("|")
    else (space)
    printf(" ");
  }
  printf("%s ", name);
  if (type == 1)
    printf("= REGISTRE :");
  else if (type == 2)
    printf("= DIRECT :");
  else if (type == 4)
    printf("= INDIRECT :");
  else if (type == 8)
    printf("= LABEL :");
  else
    printf("= UNKNOW :");
  printf("%d\n", env->pos);
}


void verif(t_elem *env)
{
  int i;
  int j;

  while(env)
  {
    i = -1;
    print(env->name, env->type, env->pos, 0);
    while(env->children[++i])
    {
      j = -1;
      print(env->children[i]->name, env->children[i]->type, env->children[i]->pos, 4)
      while(env->children[i]->children[++j])
      {
        print(env->children[i]->children[j]->name, env->children[i]->children[j]->type, env->children[i]->children[j]->pos, 8)
      }
    }
    env = env->next;
  }
}
