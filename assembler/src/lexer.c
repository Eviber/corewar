//header 42

#include "asm.h"

#define CHECK_SPACE(x) (x == ' ' || x == '\n' || x == '\t')
#define CHECK_BLANKS(x) (x == '\v' || x == '\f' || x == '\r')

//static void		parse_tab(t_elem *tree, char **tab)
//{

//}

static void		parse_line(t_elem *tree, char *line)
{
	char		*tmp;
	char		**tab;

	tmp = ft_strtrimall(line);
	if (tmp)
	{
		tab = ft_strsplit(tmp, ' ');
		ft_strdel(&tmp);
		if (tab)
		{
//			parse_tab(tree, tab);
			free_tab(&tab);
		}
	}
}

void			lexer(t_elem *tree, char *filename)
{
	int		fd;
	char		*line;
	int		ret;

	fd = open(filename, O_RDONLY);
	line = NULL;
	if (fd == -1)
		ft_putendl("error opening the file");
	else
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			parse_line(tree, line);
			ft_strdel(&line);
		}
		if (ret == -1)
			ft_putendl("error reading the file");
		close(fd);
	}
	ft_putendl("bouh");
}
