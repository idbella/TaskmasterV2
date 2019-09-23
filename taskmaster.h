/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:07:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 01:00:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKMASTER_H
# define TASKMASTER_H
# include "parser/parser.h"
#include <sys/stat.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <sys/un.h>
#include <stdio.h>

void	ft_start(t_app *app, t_params *params);
void	ft_stop(t_app *app, t_params *params);
void	ft_status(t_app *app, t_params *params);
void    ft_reload(char *file);
#endif