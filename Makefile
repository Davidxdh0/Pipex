# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dyeboa <dyeboa@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/26 14:06:32 by dyeboa        #+#    #+#                  #
#    Updated: 2022/11/05 19:19:05 by dyeboa        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= 	pipex
CC 			= 	gcc

CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address
INCLUDE 	= 	./include
VPATH 		= 	src

SRC_FILES 	=	pipex.c \
				process.c \
				free.c \
				path.c

# object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = libft.a

# Default build
all: $(OBJ_DIR) $(LIBFT) $(NAME)

# obj dir
${OBJ_DIR}	:
				mkdir -p ${OBJ_DIR}

# Libft
$(LIBFT)	:
				make -C libft
# Build 
${NAME}		: 	${OBJ_FILES} 
				$(CC) $(CFLAGS) $^ libft/$(LIBFT) -o $@

$(OBJ_FILES): 	$(OBJ_DIR)/%.o : %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -rf ${OBJ_DIR}
				make fclean -C libft/

fclean		:	clean
				rm -rf ${NAME}

re 			: 	fclean all

.PHONY 		: 	clean fclean all 