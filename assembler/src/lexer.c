//header 42

#include "asm.h"

#define CHECK_SPACE(x) (x == ' ' || x == '\n' || x == '\t')
#define CHECK_BLANKS(x) (x == '\v' || x == '\f' || x == '\r')

static size_t		get_len(char const *s)
{
	size_t			ret;
	size_t			words;

	ret = 0;
	words = 0;
	while (s && *s)
	{
		while (*s && (CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			s++;
		if (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			words++;
		while (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
		{
			s++;
			ret++;
		}
	}
	return (ret + words - 1);
}

static void			copy_str(char const *s, char **new, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		while (*s && (CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			s++;
		while (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
		{
			(*new)[i] = *s;
			i++;
			s++;
		}
		if (i < len)
		{
			(*new)[i] = ' ';
			i++;
		}
	}
}

static char			*ft_strtrimall(char const *s)
{
	char			*ret;
	size_t			len;

	len = get_len(s);
	ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (ret)
	{
		copy_str(s, &ret, len);
		return (ret);
	}
	return (NULL);
}

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
		tab = ft_strsplit(tmp);
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
