#include "asm.h"

// je part sur de la realloc au niveau de chaque instruction
// sinon avec une pre lecture y aurait surent moyen d'alloué qu'une fois

/*
** env->state
** 0 = start
** 1 = Name found
** 2 = comment found
** 3 = Header valid go read the body
*/
static void 		print_env(char *res)
{
	long	cmp;
  long taille;

  cmp = -1;
	taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(int) + sizeof(long);
	while (++cmp < taille )
	{
		if (cmp == sizeof(COREWAR_EXEC_MAGIC) || cmp == sizeof(int) + PROG_NAME_LENGTH ||
				cmp == sizeof(int) + PROG_NAME_LENGTH + sizeof(long))
			ft_printf("/");
		if (cmp && !(cmp % 64))
			ft_printf("\n");
		if (res[cmp] < 16)
			ft_printf("0");
		ft_printf("%x ", (unsigned char)res[cmp]);
	}
	ft_printf("\n");
}
// gere pas l'unicode
void ft_fill_attr(int state, char *line, t_env *env)
{
  int error;
  int i;
  int j;

  j = -1;
  error = 0;
  i = ((state == 1) ? sizeof(COREWAR_EXEC_MAGIC) :
  sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + sizeof(long));
  env->state = ((env->state) ? 3 : state);
  while(line[++j] && line[++j] != COMMENT_CHAR &&  !error)
  {
    if (line[j] == '"')
      while(line[++j] && line[j] != '"' && !error)
      {
        if (ft_strchr(LABEL_CHARS, line[j]))
          env->head[i++] = line[j];
        else if ((error = 1))
          ft_dprintf(2, "Character %c\n", line[j]);
        if (state == 1 && j > PROG_NAME_LENGTH && (error = 1))
          ft_dprintf(2, "Champion name too long (Max length %d)", PROG_NAME_LENGTH);
        if (state == 2 && j >  COMMENT_LENGTH	&& (error = 1))
          ft_dprintf(2, "Champion comment too long (Max length %d)",  COMMENT_LENGTH);
      }
    else if (!ft_isspace(line[i]) && (error = 1))
      ft_dprintf(2, "1 Lexical error at [%d:%d]\n", env->line, env->index + j);
  }
  if (error)
    exit(1);
}
/*
- Le magic (int)
- Le nom (128 bit)
- La taille du programme (long long ou long) a mettre a la fin
- Le commentaire (2048)*/

void read_attribut(t_env *env, char *line, int state)
{
  ft_printf("IN\n");
  while(ft_isspace(line[++env->index]))
    ;
  if (line[env->index] && line[env->index] != COMMENT_CHAR)
  {
    if (!ft_strncmp(line + env->index, NAME_CMD_STRING, ft_strchr(line + env->index, ' ') - line - env->index) && env->state != 1)
    {
      state = 1;
      env->index += ft_strlen(NAME_CMD_STRING);
    }
    else if (!ft_strncmp(line + env->index, COMMENT_CMD_STRING, ft_strchr(line + env->index, ' ') - line - env->index) && env->state != 2)
    {
      state = 2;
      env->index += ft_strlen(COMMENT_CMD_STRING);
    }
    else
    {
      ft_dprintf(2, "2 Lexical error at [%d:%d] %c %c: \n", env->line, env->index, COMMENT_CHAR,line[env->index] );
      exit(1);
    }
  }
  ft_printf("RE_IN\n");
  if (state)
    ft_fill_attr(state, line + env->index, env);
  ft_printf("OUT\n");
}
// search token
/*
size_t search_token(char *line, t_env *env)
{
  int i;
  int j;

  i = -1;
  while(ft_isspace(line[++i]))
    ;
  while(line[i] && line[i] != COMMENT_CHAR)
  {
    if ()
  }
}*/

int get_label(char *name, t_env *env)
{
  t_label *tmp;
  long cmp;
  long *new_tmp;

  cmp = -1;
  tmp = env->label;
  while (tmp->next && ft_strcmp(tmp->name, name))
      tmp = tmp->next;
  if (!ft_strcmp(tmp->name, name))
  {
    if (tmp->index != -1)
      return (tmp->index);
  }
  else
  {
    tmp->next = ft_memalloc(sizeof(t_label));
    tmp = tmp->next;
    tmp->name = ft_strdup(name);
    tmp->index = -1;
  }
  while (tmp->appel && tmp->appel[++cmp])
    ;
  new_tmp = ft_memalloc(sizeof(long) * (cmp + 1));
  cmp = -1;
  while (tmp->appel && tmp->appel[++cmp])
    new_tmp[cmp] = tmp->appel[cmp];
  new_tmp[cmp] = env->pos;
  free(tmp->appel);
  tmp->appel = new_tmp;
  return (0);
}

void check_param(char *src, int add, t_env *env, t_op op)
{
  static short type = 0;
  int size;
  int value;

  type = (type > 8) ? type / 8 : op.type;
  if (*src == '%' && (type & T_DIR))
    size = 4 / 1 * op.half_dir_size;
  else if ((*src == ':' || ft_isalnum(*src)) && (type & T_IND))
    size = 2;
  else if (*src == 'r' && (type & T_REG))
    size = 1;
  else if (ft_dprintf(2, "Invalid instruction at token [TOKEN][%3d:%3d] PARAMETER ""%s""[%d:%d]\n", env->line,  env->index + add, src))
    exit(1);
  if (*src == ':' || src[2] == ':')
    value = get_label(++src, env);
  else
    value = ft_atoi((size == 1 || size == 2) ? ++src : src);
  if (size == 1 && value > REG_NUMBER && ft_dprintf(2, "Invalide registre %d\n",value))
    exit(1);
  while (value && size-- && !(ft_isspace(*(++src))))
  {
    //if (!ft_isalnum(*src) && ft_dprintf(2, "Invalid instruction at token [TOKEN][%3d:%3d] PARAMETER ""%s""[%d:%d]\n", env->line,  env->index + add, src))
      //exit(1);
    env->champ[env->pos + size] =(char)value % 256;
    value = (value - (value % 256)) / 256;
  }
  env->pos += size;
}


void get_param(t_op op, char *src, t_env *env, int add)
{
  int cmp;
  int state;
  int nb_arg;

  state = 0;
  cmp = -1;
  nb_arg = 1;
  while(src[++cmp] && src[cmp] != COMMENT_CHAR)
  {
    if (ft_isspace(src[cmp]))
      state = 1;
    else if (state == 1 && src[cmp] != SEPARATOR_CHAR && (state = 2))
      check_param(src + cmp, cmp + add, env, op);
    else if (state == 2 && src[cmp] == SEPARATOR_CHAR)
    {
      if (++nb_arg > op.nb_params && ft_dprintf(2, "trop d'argument\n"))
        exit(1);
      state = 1;
    }
    else
      ft_dprintf(2, "Invalid instruction at token [TOKEN][%3d:%3d] PARAMETER ""%s""[%d:%d]\n", env->line,  env->index + cmp + add, src + cmp);
  }
}

int search_inst(char *src, t_env *env)
{
  int nb_param;
  size_t fin_src;
  int cmp;
  char octal;

  octal = 0;
  fin_src = (ft_strchr(src, ' ') - src);
  cmp = -1;
  if (fin_src > 0)
  {
    while (++cmp < 16 && ft_strncmp(src, env->op[cmp].name, fin_src))
      ;
    if (cmp < 16)
    {
      get_param(env->op[cmp], src + fin_src, env, fin_src);
      return(1);
    }
  }
  src[fin_src] = '\0';
  ft_dprintf(2, "Invalid instruction at token [TOKEN][%3d:%3d] INSTRUCTION ""%s""[%d:%d]\n", env->line,  env->index, src);
  exit(1);
}

void new_label(t_env *env, char *src, size_t end_src)
{
  t_label *tmp;

  tmp = env->label;
  if (tmp)
  {
    while(tmp->next && ft_strncmp(src, tmp->name, end_src))
      tmp = tmp->next;
    if (!ft_strncmp(src, tmp->name, end_src))
      tmp->index = env->pos;
    else
    {
      tmp->next = ft_memalloc(sizeof(t_label));
      tmp->next->name = ft_strdup(src);
    }
  }
  else
  {
    tmp = ft_memalloc(sizeof(t_label));
    tmp->name = ft_strdup(src);
  }
}

void read_champ(t_env *env, char *line)
{
  int state;

  state = 0;
  while(ft_isspace(line[++env->index]))
    ;
  while (line[env->index] && line[env->index] != COMMENT_CHAR)
  {
    if (ft_strchr(line + env->index, ':') < ft_strchr(line + env->index, ' ') && state == 0)
    {
      new_label(env, line + env->index, ft_strchr(line + env->index, ':') - line);
      env->index += (ft_strchr(line + env->index, ':') - line);
      state = 1;
    }
    else if (state != 2 && search_inst(line + env->index, env) && (state == 2))
      ;
    else
    {
      ft_dprintf(2, "3 Lexical error at [%d:%d]\n", env->line, env->index);
      exit(1);
    }
    env->index++;
  }
}

t_op *get_opt()
{
  static t_op    op_tab[17] = {
  	{"live", 1, T_DIR , 0, 0},
  	{"ld", 2, T_DIR + T_IND + T_REG * 8, 1, 0},
  	{"st", 2, T_REG + (T_IND + T_REG) * 8, 1, 0},
  	{"add", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0},
  	{"sub", 3, T_REG + (T_REG) * 8 + (T_REG) * 64, 1, 0},
  	{"and", 3, T_REG + T_DIR + T_IND + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0},
  	{"or", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0},
  	{"xor", 3, T_REG + T_IND + T_DIR + (T_REG + T_IND + T_DIR) * 8 + T_REG * 64, 1, 0},
  	{"zjmp", 1, T_DIR, 0, 1},
  	{"ldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG, 1, 1},
  	{"sti", 3, T_REG + (T_REG + T_DIR + T_IND) * 8 + (T_DIR + T_REG) * 64, 1, 1},
  	{"fork", 1, T_DIR, 0, 1},
  	{"lld", 2, T_DIR + T_IND + T_REG * 8, 1, 0},
  	{"lldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1},
  	{"lfork", 1, T_DIR, 0, 1},
  	{"aff", 1, T_REG, 1, 0},
  	{0, 0, 0, 0, 0} };

  return(op_tab);
}

t_env *init_env(void)
{
  t_env *env;
  long magic;
  int cmp;

  magic = COREWAR_EXEC_MAGIC;
  cmp = sizeof(COREWAR_EXEC_MAGIC);
  env = ft_memalloc(sizeof(t_env));
  env->taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(COREWAR_EXEC_MAGIC) + sizeof(long);
  env->head = ft_memalloc(env->taille);
  while (--cmp > -1 && magic > 0)
  {
    env->head[cmp] =(char) magic % 256;
    magic = (magic - (magic % 256)) / 256;
  }
  env->op = get_opt();
  return (env);
}


char *read_file(char *file, int error, t_env *env)
{
  char *line;
	int fd;

	line = NULL;
	fd = open(file, O_RDONLY);
  if (fd > 0 && (env = init_env()))
		while (get_next_line(fd, &line) > 0 && ++env->line)
		{
      ft_printf("env->state = %d | env->line = %d\n", env->state, env->line);
      env->index = -1;
      if (env->state < 3)
        read_attribut(env, line, 0);
      else if (env->state == 3)
        read_champ(env, line);
			ft_memdel((void **)&line);
		}
	if (error)
		ft_memdel((void **)&env);
	if (fd <= 0 )
		ft_printf("Bad file : %s\n", file);
	return(env->head);
}

void ft_exit(char *error)
{
  write(2, error, ft_strlen(error));
  exit(1);
}

char *switch_extension(char *src, char *new_extension)
{
  char *res;
  size_t cmp;
  size_t i;

  cmp = ft_strlen(src);
  while (src[--cmp] != '.')
    ;
  res = ft_memalloc(cmp + ft_strlen(new_extension) + 1);
  i = -1;
  while (++i < cmp)
    res[i] = src[i];
  cmp = -1;
  while(new_extension[++cmp])
    res[i++] = new_extension[cmp];
  return(res);
}

int main(int argc, char **argv)
{
  int fd;
  char *str;
  char *new_file;
  t_env *env;

	if (argc < 2)
		write(1, "Usage : ./corrector [outpout_lem-in]\n", 37);
  else
  {
    while(--argc > 0)
    {
      new_file = switch_extension(argv[argc], ".cor");
      fd = open(new_file, O_RDWR|O_CREAT, 0666);
      env = init_env();
      if (fd < 0)
        ft_exit("Erreur open\n");
      str = read_file(argv[argc], 0, env);
      ft_printf("Writing output program to %s\n", new_file);
      write(fd, str, env->taille);
      write(1, str, env->taille);
      close(fd);
    }
  }

	return(0);
}
