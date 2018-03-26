
#include <asm.h>

void ft_error(char *name, int error, t_token type)
{
	//ft_dprintf(2, "Compiling of %s fail : ", env->name);
	/*if (error == 1)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", env->line, env->index);
	if (error == 2)
		ft_dprintf(2, "Name too long (Max length %d)\n", PROG_NAME_LENGTH);
	if (error == 3)
		ft_dprintf(2, "Comment too long (Max length %d)\n",  COMMENT_LENGTH);
	*/if (error == 5)
		ft_dprintf(2, "Number of register %s greater than %d\n", name, REG_NUMBER);
	/*if (error == 6)
		ft_dprintf(2, "More argument in %s at line %d than allow\n", name, env->line);
	*/if (error == 7)
  {
		ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d]\n", 1,  1);
    print_token(type, -1);
    ft_dprintf(2, """%s""\n", name);
  }
  if (error == 8)
  {
		ft_dprintf(2, "Invalid parameter [parameter][%03d:%03d]\n", 1,  1);
    ft_dprintf(2, """%s""\n", name);
  }/*
  if (error == 8)
		ft_dprintf(2, "Champion too long (Max length %d)\n", CHAMP_MAX_SIZE);
	if (error == 9)
		ft_dprintf(2, "No such label %s while attempting to dereference token [TOKEN][%03d:%03d] LABEL\n", name, env->line, env->index);
	if (error == 10)
		ft_dprintf(2, "Error all the attribut are not present.\n");*/
	//env->error = 1;
  exit(1);
}
