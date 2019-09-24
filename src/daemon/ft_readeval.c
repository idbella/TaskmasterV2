/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readeval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:05:42 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:06:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_apply(t_params *params, char **argv, void (*func)())
{
	t_list	*lst;
	t_app	*app;
	int		i;

	lst = params->apps;
	while (lst)
	{
		app = lst->content;
		if (ft_strequ(argv[1], "all"))
			func(app, params);
		else
		{
			i = 1;
			while (argv[i])
			{
				if (ft_strequ(argv[i], app->name))
					func(app, params);
				i++;
			}
		}
		lst = lst->next;
	}
}

void	ft_eval(t_params *params, char **argv)
{
	if (ft_strequ("exit", argv[0]))
		exit(0);
	if (argv[1])
	{
		if (ft_strequ("status", argv[0]))
			ft_apply(params, argv, ft_status);
		else if (ft_strequ("start", argv[0]))
			ft_apply(params, argv, ft_start);
		else if (ft_strequ("restart", argv[0]))
			ft_apply(params, argv, ft_restart);
		else if (ft_strequ("stop", argv[0]))
			ft_apply(params, argv, ft_stop);
		else if (ft_strequ("reload", argv[0]))
			ft_reload(params->configfile);
	}
	else
		ft_printf_fd(params->fd, "usage : %s name\n", argv[0]);
}
