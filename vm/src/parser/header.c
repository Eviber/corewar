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
		ft_printf("number = %d\n", tmp->number);
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

//rechercher une idée pour ne jamais se retrouver

void ft_choose_number_player(t_vm *env, int num_k, int conflict, int max)
{
	t_header *tmp;
	t_header *tmp2;
	int number;

	number = 0;
	while(conflict == 1 && !(conflict = 0))
	{
		tmp = env->champion;
		while (tmp->next && (tmp2 = env->champion))
		{
			if (tmp->number == num_k && (conflict = 1))
				tmp->number++;
			number = tmp->number;
			max = ((max < tmp->number) ? number : max);
			while (tmp2->next)
			{
				if (tmp != tmp2 && (tmp2->number == num_k || tmp2->number == number) && (conflict = 1))
					tmp->number++;
				max = ((max < tmp->number) ? number : max);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	}
	tmp->number = ((num_k) ? num_k : max + 1);
}

void	ft_init_header(t_vm *env, char *line, int start, char **av)
{
	t_header *tmp;
	int number;

	number = 0;
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
	if (start > 2 && !(ft_strcmp(av[start - 2], "-n")))
			number = ft_atoi(av[start - 1]);
	ft_choose_number_player(env, number, 1, 0);
	ft_fill_header(tmp, line, -1, 0);
}
