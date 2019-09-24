/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:50:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 00:56:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_app	*ft_newapp(t_params *params, t_jsobject *js)
{
	t_app	*app;
	t_list	*node;

	app = malloc(sizeof(t_app));
	app->data = js;
	app->env = NULL;
	app->std_err = NULL;
	app->std_out = NULL;
	app->autorestart = NULL;
	app->status = 0;
	ft_bzero(app->exitcode, 256);
	app->wdir = NULL;
	app->autorestart = 0;
	app->numprocs = 0;
	app->umask = 0644;
	app->startretries = 0;
	app->starttime = 0;
	app->stopsignal = 0;
	app->pid = 0;
	node = ft_lstnew(NULL, 0);
	node->content = app;
	ft_lstadd(&params->apps, node);
	return (app);
}
