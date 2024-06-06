NAME =	minishell

CFLAGS = -Wall -Wextra -Werror -I./include -v -g -fsanitize=address

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
LIBFT_INCLUDE = -I ${LIBFT_DIR}

INCLUDES = -I ~/.brew/opt/readline/include -I ./include/ -I./libft/

READLINE = -lreadline -L ~/.brew/opt/readline/lib

SRCS = ${addprefix srcs/, error_handling.c \
		minishell.c \
		signals.c \
		builtins_export.c \
		parse.c }

OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	@cc ${CFLAGS} ${OBJ} ${READLINE} -L${LIBFT_DIR} ${INCLUDES} -lft -o ${NAME}

%.o: %.c
	cc ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	make -C ./libft

clean:
	rm -f ${OBJ}
	@make clean -C ${LIBFT_DIR}

fclean: clean
	rm -f ${NAME}
	@make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re