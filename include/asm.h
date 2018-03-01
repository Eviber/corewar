#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include <corewar.h>

typedef struct s_roquet
{
  int type;
  long pos;
  long value;
  int i;
  int j;
  int size_max;
  struct s_roquet *next;
} t_roquet;

typedef struct s_label
{
  char *name;
  long index;
  t_roquet *appel;
  struct s_label *next;
} t_label;

typedef struct		s_op
{
	char		*name;
	int		nb_params;
	short		type;
	int		has_octal;
	int		half_dir_size;
  int opcode;
}			t_op;


typedef struct s_env
{
  char *res;
  char *champ;
  long pos;
  long pos_last_inst;
  long index;
  int state;
  long line;
  size_t taille;
  t_label *label;
  t_op *op;
  struct s_env *next;
} t_env;
