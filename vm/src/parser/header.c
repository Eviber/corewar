#include "vm.h"

void	ft_print_head(t_vm *env)
{
	t_header	*tmp;
	int			cmp;
	int			nb_line;

	tmp = env->champion;
	while (tmp)
	{
		ft_printf("\nmagic = %x\n", tmp->magic);
		ft_printf("name =%s\n", tmp->prog_name);
		ft_printf("taille = %lu\n", tmp->prog_size);
		ft_printf("comment = %s\n\n", tmp->comment);
		tmp = tmp->next;
	}
	cmp = -1;
	nb_line = 0;
	while (cmp++ < MEM_SIZE - 1)
	{
		if (cmp && !(cmp % 64) && (nb_line += 1))
			ft_printf("\n");
		if (env->memory[cmp] < 16)
			ft_printf("0");
		ft_printf("%x ", env->memory[cmp]);
	}
	ft_printf("\n");
}

void	ft_fill_header(t_header *tmp, char *line, unsigned long i, int error)
{
	while(++i < COMMENT_LENGTH + 4 + 8 + PROG_NAME_LENGTH && !error)
	{
		if (i < sizeof(unsigned int))
			tmp->magic = tmp->magic * 256 + (unsigned char)line[i];
		else if (i < PROG_NAME_LENGTH + sizeof(unsigned int))
		{
			if (!ft_strchr(LABEL_CHARS, line[i]) && (error = 1))
				ft_dprintf(2, "Character %c non valide dans le nom\n", line[i]);
			tmp->prog_name[i - sizeof(unsigned int)] = line[i];
		}
		else if (i < PROG_NAME_LENGTH + sizeof(long) + sizeof(unsigned int))
			tmp->prog_size = tmp->prog_size * 256 + (unsigned char)line[i];
		else
		{
			if (!ft_strchr(LABEL_CHARS, line[i]) && (error = 1))
				ft_dprintf(2, "Character %c non valide = commentaire\n", line[i]);
			tmp->comment[i - 4 - 8 - PROG_NAME_LENGTH] = line[i];
		}
	}
	if (error)
		exit(1);
	if (tmp->magic != COREWAR_EXEC_MAGIC)
		ft_exit("MAGIC ne correspond pas\n");
	if (tmp->prog_size > CHAMP_MAX_SIZE)
		ft_exit("Le champion est trop long\n");
}

void	ft_init_header(t_vm *env, char *line)
{
	t_header *tmp;

	if (env->champion && (tmp = env->champion))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_header));
		tmp = tmp->next;
	}
	else
	{
		env->champion = ft_memalloc(sizeof(t_header));
		tmp = env->champion;
	}
	ft_fill_header(tmp, line, -1, 0);
}
