# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 10:50:54 by tkurukul          #+#    #+#              #
#    Updated: 2025/01/10 18:23:58 by tkurukul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRC = ft_hexconv.c ft_punt.c ft_putcharr.c ft_putnbr.c\
		ft_putstr.c ft_unputnbr.c ft_printf.c

OBJECTS = ${SRC:.c=.o}

all : $(NAME)

$(NAME):$(OBJECTS)
		ar rc $(NAME) $(OBJECTS)

%.o: %.c
		${CC} -c ${CFLAGS} -I. $< -o $@

clean:
		rm -rf $(OBJECTS)

fclean:
		rm -rf $(NAME) $(OBJECTS)

re: fclean all

.PHONY: all clean fclean re
