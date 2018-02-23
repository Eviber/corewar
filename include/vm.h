#ifndef VM_H
# define VM_H

# include "corewar.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>

# define PARAM_ONE(x)	(x >> 6) & IND_CODE
# define PARAM_TWO(x)	(x >> 4) & IND_CODE
# define PARAM_THR(x)	(x >> 2) & IND_CODE

typedef void (*t_op)(t_process *, t_vm *);
/*
** Parser
*/
void			ft_print_head(t_vm *env);
void			ft_init_header(t_vm *env, char *line, int start, char **av);
void			parsing(int ac, char **av, t_vm *vm, int cmp);
/*
** VM core
*/
int				check_peb(unsigned char peb, char **perm, int nb_param);
int				param_len(unsigned char peb, int mod, int nb_param);
unsigned int	get_param_value(unsigned int at, int len, t_vm *env);
t_process		*new_process(t_process *src, unsigned int new_pc, t_vm *env);
void			add_process(t_process **lst, t_process *new);
void			del_process(t_process **lst, t_process * todel);
void			exec_process(t_process *process, t_op *op_tab, t_vm *env);
void			check_process(unsigned long *last_period, t_process *process, \
				t_vm *env);
void			run_cycle(t_op *op_tab, t_vm *env);
void			set_cooldown(t_process *process, t_vm *env);
void			write_memory(unsigned int value, unsigned int address, \
				t_vm *env);
/*
** Instructions
*/
void			vm_live(t_process *process, t_vm *env);
void			vm_st(t_process *process, t_vm *env);
void			vm_fork(t_process *process, t_vm *env);
void			vm_lfork(t_process *process, t_vm *env);

#endif
