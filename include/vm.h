#ifndef VM_H
# define VM_H

# include "corewar.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>

typedef int (*t_op[16])(t_process *, t_vm *);
/*
** Parser
*/
void		ft_print_head(t_vm *env);
void		ft_init_header(t_vm *env, char *line, int start, char **av);
void		parsing(int ac, char **av, t_vm *vm, int cmp);
/*
** VM core
*/
t_process	*new_process(t_process *src, unsigned int new_pc, t_vm *env);
void		add_process(t_process **lst, t_process *new);
void		del_process(t_process *lst, t_process * todel);
void		exec_process(t_process *process, t_op op_tab, t_vm *env);
void		check_process(unsigned long *last_period, t_process *process, \
			t_vm *env);

#endif
