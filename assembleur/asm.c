#include "asm.h"

// je part sur de la realloc au niveau de chaque instruction
// au final pour l'instant c'est un mastoc alloc de CHAMP_MAX_SIZE
// d'ailleur du coup je si on ecrit une champ plus grand ca devrait segf
// sinon avec une pre lecture y aurait surent moyen d'alloué qu'une fois
// pense a gerer les attribut sur plusiueur ligne surtout le commentaire
//


/*
** env->state
** 0 = start
** 1 = Name found
** 2 = comment found
** 3 = Header valid go read the body
*/
void ft_error(t_env *env, char *name, int error)
{
  if (error == 1)
    ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
  if (error == 2)
    ft_dprintf(2, "Champion name too long (Max length %d)\n", PROG_NAME_LENGTH);
  if (error == 3)
    ft_dprintf(2, "Champion comment too long (Max length %d)\n",  COMMENT_LENGTH);
  if (error == 4)
    ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] PARAMETER ""%s""\n", env->line,  env->index, name);
  if (error == 5)
    ft_dprintf(2, "Number of register %s greater %d\n", name, REG_NUMBER);
  if (error == 6)
    ft_dprintf(2, "More argument in %s at line %d than allow\n", name, env->line);
  if (error == 7)
    ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] INSTRUCTION ""%s""\n", env->line,  env->index, name);
  if (error == 8)
    ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
  if (error==9)
      ft_dprintf(2, "No such label %s while attempting to dereference token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
  exit(1);
}

static void 		print_env(char *res, t_env *env)
{
	long	cmp;
  long taille;

  cmp = -1;
	taille = env->pos;
	while (++cmp <= taille )
	{
		if (cmp == sizeof(COREWAR_EXEC_MAGIC) || cmp == sizeof(int) + PROG_NAME_LENGTH ||
				cmp == sizeof(int) + PROG_NAME_LENGTH + sizeof(long))
			ft_printf("/");
		if ((cmp && !(cmp % 64)) || cmp == env->taille)
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
        if (state == 1 && j > PROG_NAME_LENGTH && (error = 1))
          ft_error(env, NULL, 2);
        if (state == 2 && j >  COMMENT_LENGTH	&& (error = 1))
          ft_error(env, NULL, 3);
        env->res[i++] = line[j];
      }
    else if (!ft_isspace(line[i]) && (env->index += j))
      ft_error(env, NULL, 1);
  }
}
/*
- Le magic (int)
- Le nom (128 bit)
- La taille du programme (long long ou long) a mettre a la fin
- Le commentaire (2048)*/

void read_attribut(t_env *env, char *line, int state)
{
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
      ft_error(env, NULL, 1);
  }
  if (state)
    ft_fill_attr(state, line + env->index, env);
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

void load_new_roquet(t_label *target, t_env *env, char current_type, int size)
{
  t_roquet *tmp;
  t_roquet *new_roquet;

  tmp = target->appel;
  new_roquet = ft_memalloc(sizeof(t_roquet));
  new_roquet->type = current_type;
  new_roquet->value = env->pos_last_inst;
  new_roquet->pos = env->pos;
  new_roquet->i = env->index;
  new_roquet->j = env->line;
  new_roquet->size_max = size;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    tmp->next = new_roquet;
  else
    target->appel = new_roquet;
}

int get_label(char *name, t_env *env, char current_type, int size)
{
  t_label *tmp;
  char    tmp_char;
  int i;

  i = 0;
  while (name[i] && !(ft_isspace(name[i])) && name[i] != SEPARATOR_CHAR)
    i++;
  tmp_char = name[i];
  name[i] = '\0';
  tmp = env->label;
  while (tmp->next && ft_strcmp(tmp->name, name))
      tmp = tmp->next;
  if (!ft_strcmp(tmp->name, name))
  {
    if (tmp->index != -1)
      return (tmp->index - env->pos_last_inst);
  }
  else
  {
    if (tmp && (tmp->next = ft_memalloc(sizeof(t_label))))
      tmp = tmp->next;
    else if ((env->label = ft_memalloc(sizeof(t_label))))
      tmp = env->label;
    tmp->name = ft_strdup(name);
    tmp->index = -1;
  }
  load_new_roquet(tmp, env, current_type, size);
  name[i] = tmp_char;
  return (0);
}

int check_int_param(char *str, t_env *env, long i)
{
  while(str[++i] && str[i]!= SEPARATOR_CHAR && !ft_isspace(str[i]))
    if (!ft_isdigit(str[i]) || str[i] == '-')
      ft_error(env, str, 4);
  return(1);
}

int check_param(char *src, t_env *env, t_op op, short type)
{
  int size;
  unsigned int value;
  int cmp;
  char current_type;

  src = src + env->index;
  if (*src == 'r' && (type & T_REG && (current_type = 1)))
    size = 1;
  else if ((*src == LABEL_CHAR || ft_isdigit(*src) || *src == '-') && (type & T_IND) && (current_type = 3))
    size = 2;
  else if (*src == DIRECT_CHAR && (type & T_DIR) && (current_type = 2))
    size = 4 / ((op.half_dir_size) ? 2 : 1);
  else
    ft_error(env, src, 4);
  if (*src == LABEL_CHAR || (src[1] == LABEL_CHAR && ++src))
    value = get_label(++src, env, current_type, size);
  else if (check_int_param(src , env, !ft_isdigit(*src)))
    value = ft_atoi((!ft_isdigit(*src)) ? ++src : src);
  if ((cmp = size) && size == 1 && value > REG_NUMBER)
    ft_error(env, src, 5);
  while (value && cmp--)
  {
    env->champ[env->pos + cmp] =(char)value % 256;
    value = (value - (value % 256)) / 256;
  }
  env->pos += size;;
  return (current_type);
}


void get_param(t_op op, char *src, t_env *env)
{
  int state;
  int nb_arg;
  short type;
  int pos;
  unsigned char octal;

  state = 0;
  nb_arg = 1;
  pos = 0;
  type = op.type;
  env->champ[env->pos++] = op.opcode;
  //ft_printf("env->pos = %d = %d\n", env->res[env->pos - 1], op.opcode);
  if (op.has_octal)
    pos = env->pos++;
  while(src[env->index] && src[env->index] != COMMENT_CHAR)
  {
    ft_printf("%s : |%c| : state = %d\n", src + env->index, src[env->index], state);
    if (ft_isspace(src[env->index]))
      /*state = (state != 1 && state < 3) ? state + 1 : state*/;
    else if (state == 0 && src[env->index] != SEPARATOR_CHAR && (state = 1))
      octal = octal * 4 + check_param(src, env, op, type);
    else if ((state == 1 || state == 3) && src[env->index] == SEPARATOR_CHAR)
    {
      if (++nb_arg > op.nb_params)
        ft_error(env, op.name, 6);
      state = 0;
      type /= 8;
    }
    else if (state != 1)
    {
      ft_printf("here • ? \n");
      ft_error(env, op.name, 4);
    }

    ++env->index;
  }
  if (pos)
  {
    while(octal < 64)
      octal *= 4;
    env->champ[pos] = octal;
    //ft_printf("octal = %b\n", octal * 4);
  }
  //ft_printf("Done : %c\n", src[env->index]);
}

int find_next_instruction(char *src)
{
  int i;

  i = -1;
  while (src[++i] && src[i] != LABEL_CHAR && src[i] != DIRECT_CHAR && src[i] != COMMENT_CHAR && src[i] != SEPARATOR_CHAR && !ft_isspace(src[i]))
    ;
  if (src[i])
    return (i);
  else
    return(i);
}

int search_inst(char *src, t_env *env)
{
  int nb_param;
  size_t fin_src;
  char octal;
  int cmp;

  cmp = -1;
  octal = 0;
  fin_src= find_next_instruction(src + env->index);
  //ft_printf("src = %s\n",src + env->index);
  cmp = -1;
  ft_printf("fin src = %d\n", fin_src);
  if (fin_src > 0)
  {
    while (++cmp < 16 && ft_strncmp(src + env->index, env->op[cmp].name, fin_src))
      /*ft_printf("%s != %s = %d\n",src + env->index, env->op[cmp].name, ft_strncmp(src + env->index, env->op[cmp].name, fin_src))*/;
    if (cmp < 16)
    {
      env->index += fin_src;
      env->pos_last_inst = env->pos;
      get_param(env->op[cmp], src, env);
      return(1);
    }
  }
  src[env->index + fin_src] = '\0';
  ft_error(env, src + env->index, 7);
  return(0);
}

void new_label(t_env *env, char *src, size_t end_src)
{
  t_label *tmp;
  char tmp_char;

  tmp_char = src[end_src];
  src[end_src] = '\0';
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
    env->label = ft_memalloc(sizeof(t_label));
    tmp = env->label;
    tmp->name = ft_strdup(src);
  }
  tmp->index = env->pos;
  src[end_src] = tmp_char;
}

int find_next(char *src, char car)
{
  int i;

  i = -1;
  while (src[++i] && src[i] != car)
    ;
  if (src[i] == car)
    return (i);
  else
    return (0);
}

int is_label(char *src, int start, t_env *env)
{
  while(src[start])
  {
    if (src[start] == LABEL_CHAR)
      return (1);
    else if (!ft_strchr(LABEL_CHARS, src[start]))
      return(0);
    if (ft_isspace(src[start]))
      return(0);
    ++start;
  }
  return(0);
}

void read_champ(t_env *env, char *line)
{
  int state;
  long next_space;
  long next_label_token;

  state = 0;
  next_space = find_next_instruction(line);
  next_label_token = find_next(line, LABEL_CHAR);
  while (line[++env->index] && line[env->index] != COMMENT_CHAR && state != 2)
  {
    if (ft_isspace(line[env->index]))
      ;
    else if (state == 0 && is_label(line, env->index, env))
    {
      ft_printf("index = %d : %c\n", env->index, line[env->index]);
      new_label(env, line, ft_strchr(line + env->index, LABEL_CHAR) - line);
      env->index += (ft_strchr(line + env->index, LABEL_CHAR) - line);
      state = 1;
    }
    else if (state != 2 && search_inst(line, env) && (state = 2))
      ;
    else
    {
      ft_printf("Here ¿\n");
      ft_error(env, NULL, 1);
    }
  }
}

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
  	{"ldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG, 1, 1, 10},
  	{"sti", 3, T_REG + (T_REG + T_DIR + T_IND) * 8 + (T_DIR + T_REG) * 64, 1, 1, 11},
  	{"fork", 1, T_DIR, 0, 1, 12},
  	{"lld", 2, T_DIR + T_IND + T_REG * 8, 1, 0, 13},
  	{"lldi", 3, T_REG + T_DIR + T_IND + (T_DIR + T_REG) * 8 + T_REG * 64, 1, 1, 14},
  	{"lfork", 1, T_DIR, 0, 1, 15},
  	{"aff", 1, T_REG, 1, 0, 16},
  	{0, 0, 0, 0, 0, 15} };

  return(op_tab);
}

//pense a recupere l'ancien dans le cas ou il y a plusieur compil
//et bzero le tout mais avant change moi cette alloc
t_env *init_env(void)
{
  t_env *env;
  long magic;
  int cmp;

  magic = COREWAR_EXEC_MAGIC;
  cmp = sizeof(COREWAR_EXEC_MAGIC);
  env = ft_memalloc(sizeof(t_env));
  env->taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(COREWAR_EXEC_MAGIC) + sizeof(long) + 4;
  env->res = ft_memalloc(env->taille);
  env->champ = ft_memalloc(CHAMP_MAX_SIZE);
  while (--cmp > -1 && magic > 0)
  {
    env->res[cmp] =(char) magic % 256;
    magic = (magic - (magic % 256)) / 256;
  }
  env->op = get_opt();
  return (env);
}

void fill_length_file(t_env *env)
{
  long tmp;
  long cmp;

  tmp = env->pos;
  if (tmp > CHAMP_MAX_SIZE)
    ft_error(env, NULL, 8);
  cmp = sizeof(long);
  while(--cmp > -1 && tmp > 0)
  {
    env->res[sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + cmp] = (char) tmp % 256;
    tmp = (tmp - (tmp % 256)) / 256;
  }
}

void print_label(t_env *env)
{
  t_label *tmp;
  t_roquet *tmp2;

  tmp = env->label;
  while(tmp)
  {
    tmp2 = tmp->appel;
    ft_printf("name = %s\n", tmp->name);
    ft_printf("index = %ld\n", tmp->index);
    while(tmp2)
    {
      ft_printf("type = %d\n", tmp2->type);
      ft_printf("pos = %ld\n", tmp2->pos);
      ft_printf("size_max = %ld\n", tmp2->size_max);
      ft_printf("[%d:%d]\n",tmp2->i, tmp2->j);
      tmp2 = tmp2->next;
    }
    ft_printf("\n\n");
    tmp = tmp->next;
  }
}

void check_label(t_env *env, unsigned int value,t_label *tmp)
{
  t_roquet *tmp2;

  tmp = env->label;
  while(tmp)
  {
    tmp2 = tmp->appel;
    if (tmp->index == -1)
    {
      env->line = tmp2->j;
      env->index = tmp2->i;
      ft_error(env, tmp->name, 9);
    }
    while(tmp2)
    {
      value = tmp->index - tmp2->value;
      while (value && tmp2->size_max--)
      {
        env->champ[tmp2->pos + tmp2->size_max] =(char)value % 256;
        value = (value - (value % 256)) / 256;
      }
      tmp2 = tmp2->next;
    }
    tmp = tmp->next;
  }
  print_label(env);
}

char *read_file(char *file, int error, t_env *env)
{
  char *line;
	int fd;
  long tmp;

	line = NULL;
	fd = open(file, O_RDONLY);
  if (fd > 0 )
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
  fill_length_file(env);
  check_label(env, 0, NULL);
	return(env->res);
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
      fd = open(new_file, O_RDWR|O_CREAT|O_TRUNC, 0666);
      env = init_env();
      if (fd < 0)
        ft_exit("Erreur open\n");
      str = read_file(argv[argc], 0, env);
      ft_printf("Writing output program to %s\n", new_file);
      write(fd, str, env->taille);
      print_env(env->champ, env);
      write(fd, env->champ, env->pos);
      close(fd);
    }
  }

	return(0);
}
