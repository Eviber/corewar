#include "asm.h"

// je part sur de la realloc au niveau de chaque instruction
// au final pour l'instant c'est un mastoc alloc de CHAMP_MAX_SIZE
// d'ailleur du coup je si on ecrit une champ plus grand ca devrait segf
// sinon avec une pre lecture y aurait surent moyen d'alloué qu'une fois

void *ft_memalloc_exit(size_t size)
{
	void *mem;
	if (!(mem = ft_memalloc(size)))
	{
		ft_dprintf(2, "Malloc has failed in this execution\n");
		exit(1);
	}
	return(mem);
}

void memory_manager(t_env *env, int size)
{
	char *save;
	long cmp;

	if (env->pos + size > CHAMP_MAX_SIZE)
		env->error = 2;
	else if (env->pos + size > env->size_champ)
	{
		cmp = -1;
		save = env->champ;
		env->champ = ft_memalloc_exit(env->pos + 40);
		while(++cmp < env->pos)
			env->champ[cmp] = save[cmp];
		ft_memdel((void**)&save);
		env->size_champ = env->pos + 40;
	}
}

void ft_error(t_env *env, char *name, int error)
{
	ft_dprintf(2, "Compiling of %s fail : ", env->name);
	if (error == 1)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
	if (error == 2)
		ft_dprintf(2, "Name too long (Max length %d)\n", PROG_NAME_LENGTH);
	if (error == 3)
		ft_dprintf(2, "Comment too long (Max length %d)\n",  COMMENT_LENGTH);
	if (error == 4)
		ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] PARAMETER ""%s""\n", env->line,  env->index, name);
	if (error == 5)
		ft_dprintf(2, "Number of register %s greater than %d\n", name, REG_NUMBER);
	if (error == 6)
		ft_dprintf(2, "More argument in %s at line %d than allow\n", name, env->line);
	if (error == 7)
		ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] INSTRUCTION ""%s""\n", env->line,  env->index, name);
	if (error == 8)
		ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
	if (error == 9)
		ft_dprintf(2, "No such label %s while attempting to dereference token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
	if (error == 10)
		ft_dprintf(2, "Error all the attribut are not present.\n");
	env->error = 1;
}

void print_label(t_env *env)
{
	t_label *tmp;
	t_roquet *tmp2;

	tmp = env->label;
	while(tmp)
	{
		tmp2 = tmp->appel;
		ft_printf("name = |%s|\n", tmp->name);
		ft_printf("index = %ld\n", tmp->index);
		while(tmp2)
		{
			ft_printf("pos = %ld\n", tmp2->pos);
			ft_printf("size_max = %ld\n", tmp2->size_max);
			ft_printf("[%d:%d]\n",tmp2->i, tmp2->j);
			tmp2 = tmp2->next;
		}
		ft_printf("\n\n");
		tmp = tmp->next;
	}
}

void fill_memory(char *mem, long value, int size, int start)
{
	while (value && size--)
	{
		mem[start + size] =(char)value % 256;
		value = (value - (value % 256)) / 256;
	}
}

/*
   static void 		print_env(char *res, t_env *env)
   {
   unsigned long	cmp;
   unsigned long taille;

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
   }*/

int ft_fill_attr(char *line, t_env *env, char state)
{
	while(line[++env->index] && line[env->index] != COMMENT_CHAR && !env->error)
	{
		if (line[env->index] == '"' && !(state & 4) && state & 1)
			state |= ((state & 2) ? 4 : 2);
		else if (line[env->index] == '"' && !(state & 32) && state & 8)
			state |= ((state & 16) ? 32 : 16);
		else if ((state & 1 && !(state & 2)) && env->pos - sizeof(COREWAR_EXEC_MAGIC) > PROG_NAME_LENGTH )
			ft_error(env, NULL, 2);
		else if ((state & 8 && !(state & 16)) && env->pos - sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + sizeof(long) > COMMENT_LENGTH)
			ft_error(env, NULL, 3);
		else if (!ft_isspace(line[env->index]) && (((state & 2) && (state & 4)) || (!(state & 2) && !(state & 4))) && (((state & 32) && (state & 16)) || ((state & 32) && (state & 16))))
			ft_error(env, NULL, 1);
		else if (((state & 2) && !(state & 4)) || ((state & 16) && !(state & 32)))
			env->res[env->pos++] = line[env->index];
	}
	if (((state & 2) && !(state & 4)) || ((state & 16) && !(state & 32)))
		env->res[env->pos++] = '\n';
	return(state);
}

/*
 ** state binaire = etat de la recherche de attr
 ** 0b00000000 = nothing find
 ** 0b00xxx001 = .name find
 ** 0b00xxx011 = char *name find
 ** 0b00xxx111 = char *name finish
 ** 0b00001xxx = .comment find
 ** 0b00011xxx = char *comment find
 ** 0b00111xxx = char *comment finish
 ** 0b00111111 = attribut finis;
 */

char   search_attr(char *line, t_env *env, char state)
{
	while (line[++env->index] && line[env->index] != COMMENT_CHAR && !env->error)
	{
		if (ft_isspace(env->index))
			;
		else if (!ft_strncmp(line + env->index, NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)) && !(state & 1))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC);
			env->index += ft_strlen(NAME_CMD_STRING) - 1;
			return (state | 1);
		}
		else if (!ft_strncmp(line + env->index, COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)) && !(state & 8))
		{
			env->pos = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + sizeof(long);
			env->index += ft_strlen(COMMENT_CMD_STRING) - 1;
			return (state | 8);
		}
		else
			ft_error(env, NULL, 10);
	}
	return (state);
}

void read_attribut(t_env *env, char *line)
{
	static char state = 0;

	if (env->state == 0 && (env->state = 1))
		state = 0;
	if ((!(state & 2) || (state & 2 && state & 4 && !(state & 8)))  && ((!(state & 16)) || (state & 16 && state & 32 && !(state & 2))))
		state = search_attr(line, env, state);
	if (((state & 1) && !(state & 4)) || ((state & 8) && !(state & 32)))
		state = ft_fill_attr(line, env, state);
	if (state == 63)
		env->state = 2;
}

void load_new_roquet(t_label *target, t_env *env, int size)
{
	t_roquet *tmp;
	t_roquet *new_roquet;

	tmp = target->appel;
	new_roquet = ft_memalloc_exit(sizeof(t_roquet));
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

int get_label(char *name, t_env *env, int i, int size)
{
	t_label *tmp;
	char    tmp_char;

	while (name[i] && !(ft_isspace(name[i])) && name[i] != SEPARATOR_CHAR)
		i++;
	tmp_char = name[i];
	name[i] = '\0';
	tmp = env->label;
	while (tmp && tmp->next && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->name, name))
		if (tmp->index != -1)
			return (tmp->index - env->pos_last_inst);
	if (!(tmp && !ft_strcmp(tmp->name, name)))
	{
		if (tmp && (tmp->next = ft_memalloc_exit(sizeof(t_label))))
			tmp = tmp->next;
		else if ((env->label = ft_memalloc_exit(sizeof(t_label))))
			tmp = env->label;
		tmp->name = ft_strdup(name);
		tmp->index = -1;
	}
	name[i] = tmp_char;
	load_new_roquet(tmp, env, size);
	return (0);
}

int check_int_param(char *str, t_env *env, long i)
{
	while(str[++i] && str[i]!= SEPARATOR_CHAR &&
    !ft_isspace(str[i]) && !env->error)
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
	else if (!(size = 0))
		ft_error(env, src, 4);
	if (!(value = 0) && (*src == LABEL_CHAR || (src[1] == LABEL_CHAR && ++src)))
		value = get_label(++src, env, 0, size);
	else if (check_int_param(src , env, !ft_isdigit(*src)))
		value = ft_atoi((!ft_isdigit(*src) && (*src != '-')) ? ++src : src);
	if ((cmp = size) && size == 1 && value > REG_NUMBER)
		ft_error(env, src, 5);
	memory_manager(env, cmp);
	fill_memory(env->champ, value, cmp, env->pos);
	env->pos += size;
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
	memory_manager(env, 1);
	env->champ[env->pos++] = op.opcode;
	if (op.has_octal)
		pos = env->pos++;
	while(src[env->index] && src[env->index] != COMMENT_CHAR && !env->error)
	{
		if (ft_isspace(src[env->index]))
      ;
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
			ft_error(env, op.name, 4);
		++env->index;
	}
	if (pos)
	{
		while(octal < 64)
			octal *= 4;
		memory_manager(env, 1);
		env->champ[pos] = octal;
		}
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

	nb_param = 0;
	cmp = -1;
	octal = 0;
	fin_src= find_next_instruction(src + env->index);
	cmp = -1;
	while (++cmp < 16 && ft_strncmp(src + env->index, env->op[cmp].name, fin_src))
		;
	if (cmp < 16)
	{
		env->index += fin_src;
		env->pos_last_inst = env->pos;
		get_param(env->op[cmp], src, env);
		return(1);
	}
	src[env->index + fin_src] = '\0';
	ft_error(env, src + env->index, 7);
	return(0);
}

void new_label(t_env *env, char *src, size_t end_src, t_label *tmp)
{
	char tmp_char;

	tmp_char = src[end_src];
	src[end_src] = '\0';
	if (tmp)
	{
		while(tmp->next && (ft_strncmp(src, tmp->name, end_src) || ft_strlen(tmp->name) != end_src))
			tmp = tmp->next;
		if (!ft_strncmp(src, tmp->name, end_src) && ft_strlen(tmp->name) == end_src)
			tmp->index = env->pos;
		else
		{
			tmp->next = ft_memalloc_exit(sizeof(t_label));
			tmp->next->name = ft_strdup(src);
			tmp = tmp->next;
		}
	}
	else
	{
		env->label = ft_memalloc_exit(sizeof(t_label));
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

int is_label(char *src, int start)
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
	while (line[++env->index] && line[env->index] != COMMENT_CHAR && state != 2 && !env->error)
	{
		if (ft_isspace(line[env->index]))
			;
		else if (state == 0 && is_label(line, env->index))
		{
			new_label(env, line, ft_strchr(line + env->index, LABEL_CHAR) - line, env->label);
			env->index += (ft_strchr(line + env->index, LABEL_CHAR) - line);
			state = 1;
		}
		else if (state != 2 && search_inst(line, env) && (state = 2))
			;
		else
			ft_error(env, NULL, 1);
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

t_env *init_env(int option, t_env *last_env)
{
	t_env *env;
	long magic;

	magic = COREWAR_EXEC_MAGIC;
	if (option == 1)
	{
		env = ft_memalloc_exit(sizeof(t_env));
		env->op = get_opt();
	}
	else if ((env = last_env))
	{
		ft_memdel((void **)&env->res);
		ft_memdel((void **)&env->champ);
		env->line = 0;
		env->state = 0;
		env->error = 0;
	}
	env->taille = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(COREWAR_EXEC_MAGIC) + sizeof(long) + 4;
	env->label = NULL;
	env->res = ft_memalloc_exit(env->taille);
	env->champ = ft_memalloc_exit(40);
	env->size_champ = 40;
	fill_memory(env->res, magic, sizeof(COREWAR_EXEC_MAGIC), 0);
	return (env);
}

void fill_length_file(t_env *env)
{
	long tmp;

	tmp = env->pos;
	if (tmp > CHAMP_MAX_SIZE)
		ft_error(env, NULL, 8);
	fill_memory(env->res, tmp, sizeof(long), sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH);
}


void check_label(t_env *env, t_label *tmp)
{
	t_roquet *tmp2;

	tmp = env->label;
	while(tmp && !env->error)
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
			fill_memory(env->champ, tmp->index - tmp2->value,tmp2->size_max, tmp2->pos);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void check_error(t_env *env)
{
	if (!env->error)
	{
		if (env->state != 3)
			ft_error(env, NULL, 10);
		else if (env->pos == 0 && ((env->error = 1)))
			ft_dprintf(2, "This is a weak champion, there are no instruction\n");
	}
}

/*
 ** env->state
 ** 0 = start
 ** 1 = search att;
 ** 2 = Header valid go read the body
 */

char *read_file(char *file, t_env *env)
{
	char *line;
	int fd;
	long tmp;

	tmp = 0;
	line = ft_memalloc_exit(CHAMP_MAX_SIZE);
	fd = open(file, O_RDONLY);
	if (fd > 0 )
		while (get_next_line(fd, &line) > 0 && ++env->line && !env->error)
		{
			env->index = -1;
			if (env->state < 2)
				read_attribut(env, line);
			else if (env->state == 2 && (env->state = 3))
				env->pos = 0;
			else if (env->state == 3)
				read_champ(env, line);
			ft_memdel((void **)&line);
		}
	if (fd <= 0 && (env->error = 1))
		ft_dprintf(2, "Open error on : %s\n", file);
	check_error(env);
	fill_length_file(env);
	check_label(env, NULL);
	return(env->res);
}

void switch_extension(t_env *env, char *src, char *new_extension)
{
	char *res;
	size_t cmp;
	size_t i;

	cmp = ft_strlen(src);
	while (src[--cmp] != '.')
		;
	res = ft_memalloc_exit(cmp + ft_strlen(new_extension) + 1);
	i = -1;
	while (++i < cmp)
		res[i] = src[i];
	cmp = -1;
	while(new_extension[++cmp])
		res[i++] = new_extension[cmp];
	env->name = res;
}

int main(int argc, char **argv)
{
	int fd;
	t_env *env;

	if (argc < 2)
		write(2, "Usage : ./asm file.s\n", 21);
	else if ((env = init_env(1, NULL)))
		while(--argc > 0)
		{
			switch_extension(env, argv[argc], ".cor");
			fd = open(env->name, O_RDWR|O_CREAT|O_TRUNC, 0666);
			if (fd < 0 && (env->error = 1))
				ft_dprintf(2, "Open error for creation of %s\n", env->name);
			read_file(argv[argc], env);
			if (env->state == 3 && !env->error)
			{
				ft_printf("Writing output program to %s\n", env->name);
				write(fd, env->res, env->taille);
				write(fd, env->champ, env->pos);
			}
			close(fd);
			env = init_env(2, env);
		}
	return(0);
}
