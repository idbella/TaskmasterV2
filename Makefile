# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 14:12:48 by sid-bell          #+#    #+#              #
#    Updated: 2019/09/23 15:42:10 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

JSLIB = /USERS/hlamhidr/.brew/Cellar/json-c/0.13.1/lib/libjson-c.a -I /USERS/hlamhidr/.brew/include/json-c
LIB=libft/libft.a -I. -Ilibft/

SRC	= main.c\
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

SRC2 = $(patsubst %.c, read_line/%.c,\
addition.c\
auto_completion.c\
clear_line_or_window.c\
clear_readline.c\
copy_paste.c\
ctrl_d.c\
cut.c\
delete.c\
ft_read_line.c\
heredoc_line.c\
history.c\
home_end.c\
initial.c\
move_by_lines.c\
move_by_word.c\
moving_cursor.c\
output.c\
quotes.c\
reset_position.c\
selection1.c\
selection2.c\
termcap.c\
append.c)

all:
	gcc $(SRC) $(JSLIB) $(LIB) -o taskmasterd  -ltermcap
	gcc client.c $(SRC2) $(LIB) -o taskmasterctl libft/libft.a -ltermcap

