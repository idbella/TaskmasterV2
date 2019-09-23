/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:56:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 13:32:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_dup(t_app *app)
{
	int fd;
	int tty;

	tty = open("/dev/tty", O_RDWR);
	if (app->std_err)
	{
		if ((fd = open(app->std_err, O_WRONLY | O_CREAT, 0644) < 0)
			|| dup2(fd, 2) == -1)
		{
			ft_printf_fd(tty, "error opening file %s\n", app->std_err);
		}
		close(fd);
	}
	if (app->std_out)
	{
		if ((fd = open(app->std_out, O_WRONLY | O_CREAT, 0644) < 0)
			|| dup2(fd, 1) == -1)
		{
			ft_printf_fd(tty, "error opening file %s\n", app->std_out);
		}
		close(fd);
	}
	umask(app->umask);
}

void	ft_start(t_app *app, t_params *params)
{
	pid_t		pid;
	char		**env;

	ft_printf_fd(params->fd, "starting %s...\n", app->name);
	if (access(app->argv[0], F_OK))
	{
		ft_printf_fd(1, "[!] %s %s command not found\n",
			app->name, app->argv[0]);
		return ;
	}
	else if (access(app->argv[0], X_OK))
	{
		ft_printf_fd(1, "[!] %s %s permission denied\n",
			app->name, app->argv[0]);
		return ;
	}
	if (!(pid = fork()))
	{
		ft_dup(app);
		if (app->wdir)
			chdir(app->wdir);
		env = ft_envtoarr(app->env);
		execve(app->argv[0], app->argv, env);
	}
	app->status = RUNNING;
	app->pid = pid;
}
