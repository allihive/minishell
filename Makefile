NAME =	minishell

CFLAGS = -Wall -Wextra -Werror -I./include -g -fsanitize=address

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
LIBFT_INCLUDE = -I ${LIBFT_DIR}

INCLUDES = -I ~/.brew/opt/readline/include -I ./include/ -I./libft/
#get rid of brew, and figure out path for readline

READLINE = -lreadline -L ~/.brew/opt/readline/lib

SRCS = ${addprefix srcs/, error_handling.c minishell.c signals.c parse.c expand.c\
		${addprefix builtin/, builtin.c export.c pwd.c env.c}}

OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	cc ${CFLAGS} ${OBJ} ${READLINE} ${LIBFT} -L ${LIBFT_DIR} -lft -o ${NAME}

%.o: %.c
	@cc ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	make -C libft/

clean:
	@rm -f ${OBJ}
	@make clean -C libft/

fclean: clean
	@rm -f ${NAME}
	@make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re
