#ifndef ASM_H
# define ASM_H

enum T_TOKEN { LABEL, INST, PARAM, ATT, COMM };

/*
** faire une la liaison entre les nodes
*/

typedef struct	s_elem
{
  char *name;
  T_TOKEN type;
  unsigned long pos;
}				t_elem;

#endif
