NAME =	minishell

CFLAGS = -Wall -Wextra -Werror -I./include -g -fsanitize=address

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
LIBFT_INCLUDE = -I ${LIBFT_DIR}

INCLUDES = -I /usr/lib/x86_64-linux-gnu/ -I ./include/ -I./libft/ -I/usr/include
#/usr/lib/x86_64-linux-gnu/libreadline.a

READLINE = -lreadline
#/usr/lib/x86_64-linux-gnu/libreadline.a

SRCS = ${addprefix srcs/, error_handling.c minishell.c signals.c parse.c expand.c\
		${addprefix builtin/, builtin.c export.c pwd.c env.c unset.c}}

OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	cc ${CFLAGS} ${OBJ} ${LIBFT} -L ${LIBFT_DIR} -lft -o ${NAME} ${READLINE}

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
