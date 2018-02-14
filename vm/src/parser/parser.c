#include "vm.h"

void ft_exit(char *str)
{
  ft_printf("%s\n", str);
  exit(1);
}

void ft_init_header(t_vm *env, char *line)
{
  t_header *tmp;
  int i;

  i = -1;
  ft_printf("add = %p\n", env->champion);
  if (env->champion)
  {
    tmp = env->champion;
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = ft_memalloc(sizeof(t_header));
    tmp = tmp->next;
  }
  else
  {
    env->champion = ft_memalloc(sizeof(t_header));
    tmp = env->champion;
  }
  tmp->magic = (int)*line;
  while (line[++i + sizeof(int)] && i < PROG_NAME_LENGTH)
    tmp->prog_name[i] = line[i + sizeof(int)];
  tmp->prog_size = 0;
  i = -1;
  while (line[++i + sizeof(int) + sizeof(long) + PROG_NAME_LENGTH] && i < COMMENT_LENGTH)
    tmp->comment[i] = line[i + sizeof(int) + sizeof(long) + PROG_NAME_LENGTH];
}

int read_line(char *line, t_vm *env, int taille)
{
  static long acc = 0;
  long cmp;
  int state;
  char *name;

  state = 0;
  cmp = -1;
  while(++cmp < taille)
  {
    acc++;
  //  ft_str

      ft_printf("%#x ", (unsigned char)line[cmp]);
      //if (line[cmp])
        //state = 0;
      //else
        //state = 1;
    //}

  }
  return(0);
}

void ft_print_head(t_vm *env)
{
  t_header *tmp;

  tmp = env->champion;
  while(tmp)
  {
    ft_printf("magic = %x\n", tmp->magic);
    ft_printf("name =%s\n", tmp->prog_name);
    ft_printf("taille = %lu\n", tmp->prog_size);
    ft_printf("comment = %s\n", tmp->comment);
    tmp = tmp->next;
  }
}

void parsing(int ac, char **av, t_vm *env)
{
  char *line;
  int fd;
  int taille;
  int cmp;
  int error;

  ft_printf("add = %p\n",env->champion);
  error = 0;
  taille = PROG_NAME_LENGTH + COMMENT_LENGTH	+ sizeof(int) + sizeof(long);
  if (ac < 2)
    ft_exit("Usage: ./vm [champion.cor]");
  else
  {
    ft_printf("add = %p\n",env->champion);
    while(--ac > 0)
    {
      ft_printf("add = %p\n",env->champion);
      fd = open(av[ac], O_RDONLY);
      printf("fd = %d\n", fd);
      ft_printf("add = %p\n",env->champion);
      if ((cmp = read(fd, line, taille)) < taille)
        ft_exit("Header mal formaté");
printf("taille = %d != %d\n", taille, cmp);
      ft_printf("add = %p\n",env->champion);
      ft_init_header(env, line);
      ft_print_head(env);
    //  while ((taille = read(fd, line, )) > 0 && !error)
      //  error = read_line(line, env, taille);
    }
  }
}
