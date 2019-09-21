# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 14:12:48 by sid-bell          #+#    #+#              #
#    Updated: 2019/09/21 14:45:14 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB=libft/libft.a ~/.brew/Cellar/json-c/0.13.1/lib/libjson-c.a -I~/.brew/include/ -I.

SRC	= $(patsubst %.c, parser/%.c,\
ft_getarray.c\
ft_get_string.c\
ft_get_integer.c\
ft_invalid.c\
ft_loadfromjs.c\
main.c\
ft_entrys.c\
ft_env.c\
ft_newapp.c\
ft_loadjson.c)

all:
	gcc $(SRC) $(LIB)
