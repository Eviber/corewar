# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2018/02/15 18:12:47 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = 				corewar
ASM = 				asm
LIBFT =				libft/libft.a

C_RESET =			\033[0m
C_OK =				\033[32m
C_DEL =				\033[31m

PATH_LIBFT =		libft/
PATH_VM_OBJ =		$(PATH_VM)vm_objs/
PATH_ASM_OBJ =		$(PATH_ASM)asm_objs/

PATH_VM =			vm/
PATH_VM_SRC =		$(PATH_VM)src/
PATH_VM_PARS =		$(PATH_VM_SRC)parser/
PATH_VM_INST =		$(PATH_VM_SRC)instruction/
PATH_VM_VISU =		$(PATH_VM_SRC)visu/

PATH_ASM =			assembler/
PATH_ASM_SRC =		$(PATH_ASM)src/
#PATH_ASM_PARS =	$(PATH_ASM_SRC)parser/

CC =				gcc -Wall -Werror -Wextra
INC =				-I includes/ -I libft/includes/

VM_SRC =			$(PATH_VM_SRC)corewar.c
#					$(PATH_VM_SRC)*.c
#
#PARS =				$(PATH_PARS)corewar.c
#
#INST =				$(PATH_INST)corewar.c
#
#VISU =				$(PATH_VISU)corewar.c
#
OBJ =				$(patsubst $(PATH_VM_SRC)%.c, $(PATH_OBJ)%.o, $(VM_SRC))
#					$(patsubst $(PATH_VM_PARS)%.c, $(PATH_OBJ)%.o, $(VM_PARS))\
#					$(patsubst $(PATH_VM_INST)%.c, $(PATH_OBJ)%.o, $(VM_INST))\
#					$(patsubst $(PATH_VM_VISU)%.c, $(PATH_OBJ)%.o, $(VM_VISU))\
#					$(patsubst $(PATH_ASM_SRC)%.c, $(PATH_OBJ)%.o, $(ASM_SRC))\
#					$(patsubst $(PATH_ASM_PARS)%.c, $(PATH_OBJ)%.o, \
#$(ASM_PARS))

.PHONY: all clean fclean libft

all: libft $(NAME)

$(VM): $(LIBFT) $(VM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(INC) $^ -o $@
	@echo "$(C_OK)Done !$(C_RESET)"

$(ASM): $(LIBFT) $(ASM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(INC) $^ -o $@
	@echo "$(C_OK)Done !$(C_RESET)"

$(LIBFT): libft

libft:
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_VM_OBJ)%.o: $(PATH_VM_SRC)%.c
	@echo "Compiling @\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

#$(PATH_VM_OBJ)%.o: $(PATH_VM_PARS)%.c
#	@echo "Compiling @\033[K\033[1A\r"
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@
#
#$(PATH_VM_OBJ)%.o: $(PATH_VM_INST)%.c
#	@echo "Compiling @\033[K\033[1A\r"
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@
#
#$(PATH_VM_OBJ)%.o: $(PATH_VM_VISU)%.c
#	@echo "Compiling @\033[K\033[1A\r"
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@
#
#$(PATH_ASM_OBJ)%.o: $(PATH_ASM_SRC)%.c
#	@echo "Compiling @\033[K\033[1A\r"
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@
#
#$(PATH_ASM_OBJ)%.o: $(PATH_ASM_PARS)%.c
#	@echo "Compiling @\033[K\033[1A\r"
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@
#
clean:
	@rm -rf $(PATH_VM_OBJ)
	@rm -rf $(PATH_ASM_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "$(C_DEL)Object files removed.$(C_RESET)"

fclean: clean
	@rm -f $(VM)
	@rm -f $(ASM)
	@rm -f $(LIBFT)
	@echo "$(C_DEL)$(ASM), $(VM) and $(LIBFT) removed.$(C_RESET)"

test: all
	@echo "\\/\\/\\/\\/\\/\\/\\/BEGIN TEST\\/\\/\\/\\/\\/\\/\\/"
	@echo ""
	@./$(NAME)
	@echo ""
	@echo "/\\/\\/\\/\\/\\/\\/\\END TEST/\\/\\/\\/\\/\\/\\/\\"

re: fclean all
