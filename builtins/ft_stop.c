/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:59:56 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 13:32:30 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_stop(t_app *app, t_params *params)
{
	ft_printf_fd(params->fd, "stopping %s...\n", app->name);
	if (app->pid > 0)
		kill(app->pid, app->stopsignal);
	app->status = STOPED;
}
