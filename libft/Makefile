<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhsu <yhsu@hive.student.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 12:48:50 by alli              #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/06/12 11:15:03 by alli             ###   ########.fr        #
=======
#    Updated: 2024/06/07 18:08:27 by yhsu             ###   ########.fr        #
>>>>>>> bc0a6dd0b7cded12bc430d2f7ff99e82d8e099ae
#                                                                              #
# **************************************************************************** #

=======
>>>>>>> cf35bbd23533d21c45ec0cc551cd0ad95e0a22dc
NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar.c \
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr.c \
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_printf.c\
			ft_skipws.c\
			ft_split.c\
			ft_split_pipex.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c\
			get_next_line.c\
			get_next_line_utils.c\
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstclear.c\
			ft_lstdelone.c\
			ft_lstiter.c\
			ft_lstlast.c\
			ft_lstmap.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_whitespace.c\


OBJECTS = ${SOURCES:.c=.o}

%.o: %.c
	@cc ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJECTS}
	@ar -rcs ${NAME} ${OBJECTS}

clean:
	@rm -f ${OBJECTS}

fclean: clean
	@rm -f ${NAME}

re: fclean all
