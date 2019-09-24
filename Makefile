# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 14:12:48 by sid-bell          #+#    #+#              #
#    Updated: 2019/09/23 21:36:54 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB=libft/libft.a json-c/lib/libjson-c.a  -I. -Ilibft -Ijson-c/include/json-c

SRC	= main.c signal.c\
$(patsubst %.c, builtins/%.c,\
ft_start.c\
ft_stop.c\
ft_reload.c\
ft_status.c)\
$(patsubst %.c, parser/%.c,\
ft_getarray.c\
ft_get_string.c\
ft_get_integer.c\
ft_invalid.c\
ft_loadfromjs.c\
ft_loadconfig.c\
ft_entrys.c\
ft_env.c\
ft_newapp.c\
ft_sigstr.c\
ft_loadjson.c)

all:
	gcc $(SRC) $(LIB) -o taskmasterd
	gcc client.c -o taskmasterctl libft/libft.a
