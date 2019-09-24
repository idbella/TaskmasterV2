# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 14:12:48 by sid-bell          #+#    #+#              #
#    Updated: 2019/09/24 20:09:18 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE= -Isrc/include -Isrc/include/json-c

LIBFT= src/lib/libft/libft.a

LIB=$(LIBFT) src/lib/json-c/libjson-c.a

SRC	= src/daemon/taskmasterd.c src/daemon/ft_readeval.c src/daemon/signal.c\
$(patsubst %.c, src/daemon/builtins/%.c,\
ft_start.c\
ft_stop.c\
ft_restart.c\
ft_reload.c\
ft_status.c)\
$(patsubst %.c, src/daemon/parser/%.c,\
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

SRC2 = src/controller/taskmasterctl.c src/controller/socket.c \
$(patsubst %.c, src/controller/read_line/%.c,\
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
	gcc $(SRC) $(JSLIB) $(LIB) $(INCLUDE) -o taskmasterd
	gcc $(SRC2) -o taskmasterctl $(INCLUDE) $(LIBFT) -ltermcap

