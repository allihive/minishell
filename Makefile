NAME = minishell
#-g -fsanitize=address
CFLAGS = -g -Wall -Wextra -Werror -I./include


LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set platform-specific variables
ifeq ($(UNAME_S), Darwin)
    # macOS-specific settings
    READLINE_DIR = $(shell brew --prefix readline)
    INCLUDES = -I ${READLINE_DIR}/include -I ./include/ -I./libft/
    READLINE = -L ${READLINE_DIR}/lib -lreadline
else ifeq ($(UNAME_S), Linux)
    # Linux-specific settings
    INCLUDES = -I /usr/include/readline -I ./include/ -I./libft/
    READLINE = -L /usr/lib/x86_64-linux-gnu -lreadline -lncurses
endif

SRCS = ${addprefix srcs/, error_msg.c minishell.c signals.c\
	 		parse.c  parse_redir.c expand.c free.c free_utils.c builtin_utils.c pipex.c execution.c redirects.c\
	 		redirects_utils.c fd.c heredoc.c redirect_utils_in.c redirect_utils_out.c check_utils.c\
	 		get_cmd.c init.c init_utils.c get_path.c redirect_utils_append.c quote.c expand_utils.c\
			utils.c\
    	${addprefix builtin/, export_print.c export_check.c export.c pwd.c env.c unset.c echo.c exit.c cd.c}}

OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	@cc ${CFLAGS} ${OBJ} ${LIBFT} -L ${LIBFT_DIR} -lft -o ${NAME} ${READLINE}

%.o: %.c
	@cc ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	make -C libft/

clean:
	@rm -f ${OBJ} 
    # infile1 infile outfile outfile1 outfile2
	@make clean -C libft/
fclean: clean
	@rm -f ${NAME}
	@make fclean -C ${LIBFT_DIR}

re:	fclean all

.PHONY: all clean fclean re