# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 23:05:50 by akisuzuk          #+#    #+#              #
#    Updated: 2023/03/17 23:52:22 by akisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     := cc
CFLAGS := -Wall -Wextra -Werror

NAME = libft_printf.a

# ワイルドカードで一気に書きたいのに2通りの書き方どっちもうまくいかん
#SRCDIR  = ./srcs
#SRCS     = $(wildcard $(SRCDIR)/*.c)

#SRCs = ./srcs/*.c

SRCS = 	./srcs/ft_isalpha.c \
		./srcs/ft_isdigit.c \
		./srcs/ft_isalnum.c \
		./srcs/ft_isascii.c \
		./srcs/ft_isprint.c \
		./srcs/ft_strlen.c \
		./srcs/ft_memset.c \
		./srcs/ft_bzero.c \
		./srcs/ft_memcpy.c \
		./srcs/ft_memmove.c \
		./srcs/ft_strlcpy.c \
		./srcs/ft_strlcat.c \
		./srcs/ft_toupper.c \
		./srcs/ft_tolower.c \
		./srcs/ft_strchr.c \
		./srcs/ft_strrchr.c \
		./srcs/ft_strncmp.c \
		./srcs/ft_memchr.c \
		./srcs/ft_memcmp.c \
		./srcs/ft_strnstr.c \
		./srcs/ft_atoi.c \
		./srcs/ft_calloc.c \
		./srcs/ft_strdup.c \
		./srcs/ft_strjoin.c \
		./srcs/ft_substr.c \
		./srcs/ft_strtrim.c \
		./srcs/ft_split.c \
		./srcs/ft_itoa.c \
		./srcs/ft_strmapi.c \
		./srcs/ft_striteri.c \
		./srcs/ft_putchar_fd.c \
		./srcs/ft_putstr_fd.c \
		./srcs/ft_putendl_fd.c \
		./srcs/ft_putnbr_fd.c

OBJS    = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
