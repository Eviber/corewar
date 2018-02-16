#include "vm.h"

int rd(char *line, t_vm *env, unsigned long max, unsigned long pos)
{
  unsigned long cmp;

  cmp = -1;
  while (++cmp < max)
    env->memory[pos + cmp] = line[cmp];
  return (0);
}

unsigned long check_arg(int ac, char **av, t_vm *env)
{
  unsigned long	nb_champ;
  int			error;
  int			i;

  i = 0;
  error = 0;
  nb_champ = 0;
  while (++i < ac)
  {
    if (av[i][0] == '-' &&
    (!ft_strcmp(av[i] + 1, "dump") || !ft_strcmp(av[i] + 1, "n")))
    {
      i++;
      if (!ft_strcmp(av[i] + 1, "dump"))
        env->dump = ft_atoi(av[i]);
    }
    else
      nb_champ++;
  }
  if (nb_champ > MAX_PLAYERS)
    ft_exit("Too many player\n");
  if (nb_champ == 0)
    ft_exit("No player\n");
  return (nb_champ);
}

void parsing(int ac, char **av, t_vm *env, int cmp)
{
  unsigned long nb_champ;
  char *line;
  int taille;
  int fd;
  int start;

  start = 0;
  taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(int) + sizeof(long);
  line = ft_memalloc(taille);
  if (ac < 2)
    ft_exit("Usage: ./vm [champion.cor]");
  else if ((nb_champ = check_arg(ac, av, env) + 1))
    while (--nb_champ > 0)
    {
      while (av[++start][0] == '-')
        start += 1;
      fd = open(av[start], O_RDONLY);
      if ((cmp = read(fd, line, 100000)) < taille) ft_exit((fd <= 0)
      ? "Fichier inacessible\n" : "Fichier trop petit\n");
      ft_init_header(env, line, start, av, cmp);
      cmp = read(fd, line, CHAMP_MAX_SIZE);
      rd(line, env, cmp, (nb_champ - 1) * (MEM_SIZE / (ac - 1)));
      close(fd);
    }
  ft_memdel((void**)&line);
  ft_print_head(env);
}
