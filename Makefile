##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## minishell2 Makefile
##

CC	?=	gcc

SRC =	src/commands/cd.c			\
	src/commands/setenv.c			\
	src/commands/unsetenv.c			\
						\
	src/my_utils/my_atoi.c			\
	src/my_utils/my_put_error.c		\
	src/my_utils/my_putstr.c		\
	src/my_utils/my_strcat.c		\
	src/my_utils/my_strcmp.c		\
	src/my_utils/my_strcpy.c		\
	src/my_utils/my_strdup.c		\
	src/my_utils/my_strlen.c		\
	src/my_utils/my_strncmp.c		\
	src/my_utils/my_strncpy.c		\
	src/my_utils/one_dim_to_two_dim.c	\
						\
	src/parsing/array_manip.c		\
	src/parsing/close_redirections.c	\
	src/parsing/redirections.c		\
	src/parsing/semicolons_utils.c		\
	src/parsing/special_char.c		\
	src/parsing/null_commands.c	\
						\
	src/parsing/pipes/pipe_redirections.c	\
	src/parsing/pipes/pipes_utils.c			\
	src/parsing/pipes/pipes.c				\
	src/parsing/pipes/single_pipe_redirection.c	\
								\
	src/init_shell.c			\
	src/env.c				\
	src/execute.c				\
	src/main.c				\
	src/minishell.c				\
	src/print_error.c			\
	src/prompt.c				\

OBJ	=	$(SRC:.c=.o)

NAME = mysh

USER = Chetrit

CFLAGS	+=	-g -W -Wall

CPPFLAGS	+=	-I include/

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
