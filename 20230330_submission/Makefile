# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akisuzuk <akisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 23:05:50 by akisuzuk          #+#    #+#              #
#    Updated: 2023/03/30 20:17:32 by akisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC     := cc
CFLAGS := -Wall -Wextra -Werror

NAME = libftprintf.a

# ワイルドカードで一気に書きたいのに2通りの書き方どっちもうまくいかん
#SRCDIR  = ./srcs
#SRCS     = $(wildcard $(SRCDIR)/*.c)

#SRCs = ./srcs/*.c

SRCS = 	ft_printf.c \
		ft_proc_per.c \
		ft_output_1.c \
		ft_output_2.c \
		ft_output_sub.c \
		ft_putnbr_base_ull.c \
		ft_putnbr_fd_non_minus.c \
		ft_isdigit.c \
		ft_putnbr_fd.c \
		ft_strlen.c

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
