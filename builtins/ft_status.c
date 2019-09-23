/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:59:28 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 13:32:24 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

t_params	*ft_getter(t_params *params)
{
	static t_params *p;

	if (params)
		p = params;
	return (p);
}

void	ft_status(t_app *app, t_params *params)
{
	char	*status;

	if (app->status == RUNNING)
		status = "RUNNING";
	else if (app->status == STOPED)
		status = "STOPED";
	else if (app->status == 0)
		status = "-------";
	ft_printf_fd(params->fd, "%s\t\t%s\t\t%s\n", app->name,
		status, app->pid ? ft_itoa(app->pid) : "");
}
