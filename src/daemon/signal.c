/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:30:18 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 22:37:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_changestate(t_params *params, int pid, int status)
{
	t_list	*lst;
	t_app	*app;

	if (WIFSIGNALED(status))
		ft_printf_fd(params->fd, "pid %d stoped with %s\n", pid, strsignal(WTERMSIG(status)));
	else
		ft_printf_fd(params->fd, "pid %d NORMALLY stoped with code %d\n", pid, WEXITSTATUS(status));
	lst = params->apps;
	while (lst)
	{
		app = lst->content;
		if (app->pid == pid)
		{
			app->status = STOPED;		
			break ;
		}
		lst = lst->next;
	}
}

void	ft_sigchild(int sig)
{
	t_params	*params;
	int			pid;
	int			status;

	params = ft_getter(NULL);
	while(1)
	{
		pid = waitpid(WAIT_ANY, &status, WNOHANG);
		if (pid > 0)
			ft_changestate(params, pid, status);
		else
			break ;
	}
}
