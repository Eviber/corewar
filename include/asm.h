#ifndef ASM_H
# define ASM_H

typedef enum		e_token
{
	LABEL,
	INST,
	PARAM,
	ATT,
	COMM
}			t_token;

/*
** faire la liaison entre les nodes
*/

typedef struct		s_elem
{
 	char		*name;
	t_token		type;
	unsigned long	pos;
}			t_elem;

#endif
