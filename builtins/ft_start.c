/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:56:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 14:15:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"
#include <errno.h>
void	ft_dup(t_params *params, t_app *app)
{
	int fd;

	if (app->std_err)
	{
		if ((fd = open(app->std_err, O_WRONLY | O_CREAT, 0644)) < 0)
		{
			ft_printf_fd(params->logfile, "error opening file %s\n", app->std_err);
		}
		else
			dup2(fd, 2);
		close(fd);
	}
	if (app->std_out)
	{
		if ((fd = open(app->std_out, O_WRONLY | O_CREAT, 0644)) < 0)
		{
			ft_printf_fd(params->logfile, "error opening file %s\n", app->std_out);
		}
		else
			dup2(fd, 1);
		close(fd);
	}
	umask(app->umask);
}

void	ft_start(t_app *app, t_params *params)
{
	pid_t		pid;
	char		**env;
	char		*log;

	ft_printf_fd(params->fd, "starting %s...\n", app->name);
	ft_printf_fd(params->logfile, "%s starting %s...\n",
		app->name, ft_gettime());
	if (access(app->argv[0], F_OK))
	{
		ft_printf_fd(params->logfile, "[!] %s %s command not found\n",
			app->name, app->argv[0]);
		ft_printf_fd(params->fd, "%s [!] %s %s command not found\n",
			ft_gettime(), app->name, app->argv[0]);
		return ;
	}
	else if (access(app->argv[0], X_OK))
	{
		ft_printf_fd(params->logfile, "%s [!] %s %s permission denied\n",
			ft_gettime(), app->name, app->argv[0]);
		ft_printf_fd(params->fd, "[!] %s %s permission denied\n",
			app->name, app->argv[0]);
		return ;
	}
	if (!(pid = fork()))
	{
		ft_dup(params, app);
		if (app->wdir)
			chdir(app->wdir);
		env = ft_envtoarr(app->env);
		execve(app->argv[0], app->argv, env);
		ft_printf_fd(params->logfile, "%s failed to run %s : \n",
			app->name, app->argv[0], strerror(errno));
		exit(0);
	}
	app->status = RUNNING;
	app->pid = pid;
}
