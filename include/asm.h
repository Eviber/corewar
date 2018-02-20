#ifndef ASM_H
# define ASM_H

/*
** in addition to T_TEG / T_IND / T_DIR in op.h
*/

# define T_INS		16
# define T_ATT		32

/*
** faire la liaison entre les nodes
*/

typedef struct		s_op
{
	char		*name;
	int		nb_params;
	int		*type;
	char		opcode;
	int		nb_cycles;
	char		*desc;
	int		has_octal;
	int		unknown;
}			t_op;

typedef struct		s_elem
{
 	char		*name;
	int		type;
	unsigned long	pos;
	struct s_elem	**children; // si label: insts - si inst: params
	struct s_elem	*next; // si label: next label - sinon null
}			t_elem;

t_op			get_fct_app(void);
void			lexer(t_elem *tree, char *filename);

void			verif(t_elem *tree); // fonction de verif a supprimer

#endif
