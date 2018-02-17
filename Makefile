# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2018/02/16 22:31:53 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = 				corewar
ASM = 				asm

PATH_LIBFT =		libft/
LIBFT =				libft/libft.a

PATH_OBJ =			obj/

PATH_VM =			vm/
PATH_VM_SRC =		$(PATH_VM)src/
PATH_VM_PARS =		$(PATH_VM_SRC)parser/
PATH_VM_INST =		$(PATH_VM_SRC)instruction/
PATH_VM_VISU =		$(PATH_VM_SRC)visu/

PATH_ASM =			assembler/
PATH_ASM_SRC =		$(PATH_ASM)src/

VPATH =				$(PATH_VM_SRC):$(PATH_VM_PARS):$(PATH_VM_INST):\
$(PATH_VM_VISU):$(PATH_ASM_SRC)

CC =				gcc -Wall -Werror -Wextra
INC =				-I include/ -I libft/include/

VM_PARS =			parser.c

VM_INST =			

VM_VISU =			

VM_SRC =			corewar.c $(VM_PARS) $(VM_INST) $(VM_VISU)
ASM_SRC =			asm.c

VM_OBJ =			$(patsubst %.c, $(PATH_OBJ)%.o, $(VM_SRC))
ASM_OBJ =			$(patsubst %.c, $(PATH_OBJ)%.o, $(ASM_SRC))

all: libft $(ASM) $(VM)

$(VM): $(LIBFT) $(VM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(INC) $^ -o $@
	@echo "$(C_OK)Done !"

$(ASM): $(LIBFT) $(ASM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(INC) $^ -o $@
	@echo "$(C_OK)Done !"

$(LIBFT):
	make -C $(PATH_LIBFT)

$(PATH_OBJ)%.o: %.c
	@echo "Compiling @\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@make -C $(PATH_LIBFT) clean
	@echo "$(C_DEL)Object files removed."

fclean: clean
	@rm -f $(VM)
	@rm -f $(ASM)
	@make -C $(PATH_LIBFT) fclean
	@echo "$(C_DEL)$(ASM), $(VM) and $(LIBFT) removed."

test: all
	@echo "\\/\\/\\/\\/\\/\\/\\/BEGIN TEST\\/\\/\\/\\/\\/\\/\\/"
	@echo ""
	@./$(NAME)
	@echo ""
	@echo "/\\/\\/\\/\\/\\/\\/\\END TEST/\\/\\/\\/\\/\\/\\/\\"

re: fclean all

.PHONY: all clean fclean libft
