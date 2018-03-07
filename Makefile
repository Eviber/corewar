# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2018/03/07 17:02:23 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = 				corewar
ASM = 				asm

C_OK =		\033[32m
C_DEL =		\033[31m
C_RESET =	\033[0m

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

VPATH = $(PATH_VM_SRC):$(PATH_VM_PARS):$(PATH_VM_INST):$(PATH_VM_VISU):$(PATH_ASM_SRC)

CC =				gcc -g -Wall -Werror -Wextra
CFLAGS =			-I include/ -I libft/include/ `sdl2-config --cflags`
LFLAGS =			-L $(PATH_LIBFT) -lft `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf

VM_PARS =			parser.c\
					option.c\
					header.c

VM_INST =			vm_st.c\
					vm_and.c\
					vm_live.c\
					vm_ld.c\
					vm_lld.c\
					vm_add.c\
					vm_sub.c\
					vm_zjmp.c\
					vm_st.c\
					vm_or.c\
					vm_xor.c\
					vm_fork.c\
					vm_lfork.c\
					vm_sti.c\
					vm_aff.c\
					vm_ldi.c\
					vm_lldi.c

VM_VISU =			visu.c\
					visu_init.c\
					hud.c\
					matrix.c\
					visutools.c\
					hsl.c\
					sdltools.c\
					event_manager.c

VM_SRC =			$(VM_PARS)\
					$(VM_INST)\
					$(VM_VISU)\
					corewar.c\
					cycle.c\
					utility.c\
					process.c\
					execute.c\
					check.c\
					check_reg.c\
					verbose.c\
					params.c

ASM_SRC =			asm.c

VM_OBJ =			$(patsubst %.c, $(PATH_OBJ)%.o, $(VM_SRC))
ASM_OBJ =			$(patsubst %.c, $(PATH_OBJ)%.o, $(ASM_SRC))

all: $(LIBFT) $(ASM) $(VM)

$(VM): $(VM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(LFLAGS) $^ -o $@
	@echo "$(C_OK)Done !$(C_RESET)"

$(ASM): $(LIBFT) $(ASM_OBJ)
	@echo "Compiling $@ ...\033[K"
	@$(CC) $(LFLAGS) $^ -o $@
	@echo "$(C_OK)Done !$(C_RESET)"

$(LIBFT):
	make -C $(PATH_LIBFT)

$(PATH_OBJ)%.o: %.c
	@echo "Compiling @\033[K\033[1A\r"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@make -C $(PATH_LIBFT) clean
	@echo "$(C_DEL)Object files removed.$(C_RESET)"

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
