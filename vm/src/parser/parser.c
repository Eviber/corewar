#include "vm.h"


void ft_fill_header(t_header *tmp, char *line, unsigned long i, int error)
{
  while(++i < COMMENT_LENGTH + sizeof(int) + sizeof(long) + PROG_NAME_LENGTH && !error)
  {
    if (i < sizeof(unsigned int))
      tmp->magic = tmp->magic * 256 + (unsigned char)line[i];
    else if (i < PROG_NAME_LENGTH + sizeof(unsigned int))
    {
      if (!ft_strchr(LABEL_CHARS, line[i]) && (error = 1))
        ft_dprintf(2, "Character %c non valide dans le nom\n", line[i]);
      tmp->prog_name[i - sizeof(unsigned int)] = line[i];
    }
    else if (i < PROG_NAME_LENGTH + sizeof(long) +sizeof(unsigned int))
      tmp->prog_size = tmp->prog_size * 256 + (unsigned char)line[i];
    else
    {
      if (!ft_strchr(LABEL_CHARS, line[i]) && (error = 1))
        ft_dprintf(2, "Character %c non valide dans le commentaire\n", line[i]);
      tmp->comment[i - sizeof(int) - sizeof(long) - PROG_NAME_LENGTH] = line[i];
    }
  }
  if (error)
    exit(1);
  if (tmp->magic != COREWAR_EXEC_MAGIC)
    ft_exit("MAGIC ne correspond pas\n");
  if (tmp->prog_size > CHAMP_MAX_SIZE)
    ft_exit("Le champion est trop long\n");
}

void ft_init_header(t_vm *env, char *line)
{
  t_header *tmp;

  if (env->champion && (tmp = env->champion))
  {
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
  ft_fill_header(tmp, line, -1, 0);
}

int read_line(char *line, t_vm *env, unsigned long taille, unsigned long position)
{
  unsigned long cmp;

  cmp = -1;
  while(++cmp < taille)
    env->memory[position + cmp] = line[cmp];
  return(0);
}

void ft_print_head(t_vm *env)
{
  t_header *tmp;

  tmp = env->champion;
  while(tmp)
  {
    ft_printf("\nmagic = %x\n", tmp->magic);
    ft_printf("name =%s\n", tmp->prog_name);
    ft_printf("taille = %lu\n", tmp->prog_size);
    ft_printf("comment = %s\n\n", tmp->comment);
    tmp = tmp->next;
  }

  int cmp;
  int nb_line;
  cmp = -1;
  nb_line =0;
  while(cmp++ < MEM_SIZE - 1)
  {
    if (cmp && !(cmp % 64))
    {
      ft_printf("\n");
      nb_line++;
    }

    if (env->memory[cmp] < 16)
      ft_printf("0");
    ft_printf("%x ", env->memory[cmp]);
  }
  ft_printf("\n");
}

void parsing(int ac, char **av, t_vm *env)
{
  char *line;
  int taille;
  int nb_champ;
  int cmp;
  int fd;

  cmp = 0;
  nb_champ = ac;
  taille = PROG_NAME_LENGTH + COMMENT_LENGTH	+ sizeof(int) + sizeof(long);
  line = ft_memalloc(taille);
  if (ac < 2)
    ft_exit("Usage: ./vm [champion.cor]");
  else
    while(--nb_champ > 0)
    {
      fd = open(av[nb_champ], O_RDONLY);
      if (read(fd, line, taille + 4) < taille)
        ft_exit((fd <= 0) ? "Fichier inacessible\n" : "Header mal formaté\n");
      ft_init_header(env, line);
      cmp = read(fd, line, CHAMP_MAX_SIZE);
      read_line(line, env, cmp, (nb_champ - 1) * (MEM_SIZE / (ac - 1)));
      close(fd);
    }
  ft_memdel((void**)&line);
  //ft_print_head(env);
}
