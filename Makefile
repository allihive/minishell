# NAME =	minishell

# CFLAGS = -Wall -Wextra -Werror -I./include -g -fsanitize=address

# LIBFT_DIR = ./libft
# LIBFT = ./libft/libft.a
# LIBFT_INCLUDE = -I ${LIBFT_DIR}

# UNAME_S := $(shell uname -s)

# # Set platform-specific variables
# ifeq ($(UNAME_S), Darwin)
#     # macOS-specific settings
#     READLINE_DIR = $(shell brew --prefix readline)
# 	INCLUDES = -I ${READLINE_DIR}/include -I ./include/ -I./libft/
# 	READLINE = -L ${READLINE_DIR}/lib -lreadline
# else ifeq ($(UNAME_S), Linux)
#     # Linux-specific settings
#     INCLUDES = -I /usr/lib/x86_64-linux-gnu/ -I ./include/ -I./libft/ -I/usr/include
# 	READLINE = -lreadline
# endif

# INCLUDES = -I /usr/lib/x86_64-linux-gnu/ -I ./include/ -I./libft/ -I/usr/include
# #/usr/lib/x86_64-linux-gnu/libreadline.a

# READLINE = -lreadline
# #/usr/lib/x86_64-linux-gnu/libreadline.a

# SRCS = ${addprefix srcs/, error_handling.c minishell.c signals.c parse.c expand.c\
# 		${addprefix builtin/, builtin.c export.c pwd.c env.c unset.c}}

# OBJ = ${SRCS:.c=.o}

# all: ${NAME}

# ${NAME}: ${LIBFT} ${OBJ}
# 	cc ${CFLAGS} ${OBJ} ${LIBFT} -L ${LIBFT_DIR} -lft -o ${NAME} ${READLINE}

# %.o: %.c
# 	@cc ${CFLAGS} ${INCLUDES} -c $< -o $@

# ${LIBFT}:
# 	make -C libft/

# clean:
# 	@rm -f ${OBJ}
# 	@make clean -C libft/

# fclean: clean
# 	@rm -f ${NAME}
# 	@make fclean -C ${LIBFT_DIR}

# re: fclean all

# .PHONY: all clean fclean re

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -I./include -g -fsanitize=address

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

SRCS = ${addprefix srcs/, error_handling.c minishell.c signals.c parse.c expand.c\
        ${addprefix builtin/, builtin.c export.c pwd.c env.c unset.c echo.c}}

OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	cc ${CFLAGS} ${OBJ} ${LIBFT} -L ${LIBFT_DIR} -lft -o ${NAME} ${READLINE}

%.o: %.c
	cc ${CFLAGS} ${INCLUDES} -c $< -o $@

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
