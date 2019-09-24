/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:07:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:09:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKMASTER_H
# define TASKMASTER_H
# include "parser.h"
#include <sys/stat.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h> 
#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include "read_line.h"
#define NAME "SOCK"

void	ft_start(t_app *app, t_params *params);
void	ft_stop(t_app *app, t_params *params);
void	ft_status(t_app *app, t_params *params);
void    ft_reload(char *file);
void	ft_restart(t_app *app);
void	ft_sigchild(int sig);
int	    ft_init_sock(char *argv);
void	ft_apply(t_params *params, char **argv, void (*func)());
void	ft_eval(t_params *params, char **argv);
#endif
