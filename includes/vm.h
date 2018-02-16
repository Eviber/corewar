#ifndef VM_H
# define VM_H

# include "corewar.h"
# include <fcntl.h>
# include <unistd.h>

void	ft_print_head(t_vm *env);
void	ft_init_header(t_vm *env, char *line);
void	parsing(int ac, char **av, t_vm *vm, int cmp);

#endif
