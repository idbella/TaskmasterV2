/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:06:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 13:39:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"
#define NAME "SOCK"

static void	ft_init(t_params *params)
{
	params->logfile = open("log", O_WRONLY|O_CREAT|O_APPEND, 0644);
	params->entrys = NULL;
	params->apps = NULL;
	ft_fill_entrys(params);
}

void ft_restart(t_app *app)
{
	ft_printf_fd(1, "restarting %s...\n", app->name);
}

void ft_apply(t_params *params, char **argv, void (*func)())
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

int		ft_init_socket()
{
	int					sock;
	struct sockaddr_un	server;

	if (!access(NAME, F_OK))
		remove(NAME);
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	server.sun_family = AF_UNIX;
	ft_strcpy(server.sun_path, NAME);
	bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un));
	return (sock);
}


void	ft_loop(t_params *params, int sock)
{
	char	*line;
	char	**argv;
	int		msgsock;

	listen(sock, 5);
	while (1)
	{
		msgsock = accept(sock, 0, 0);
		params->fd = msgsock;
		while (get_next_line(msgsock, &line) > 0)
		{
			argv = ft_strsplit(line, ' ');
			if (ft_strequ("status", argv[0]))
				ft_apply(params, argv, ft_status);
			else if (ft_strequ("start", argv[0]))
				ft_apply(params, argv, ft_start);
			else if (ft_strequ("restart", argv[0]))
				ft_apply(params, argv, ft_restart);
			else if (ft_strequ("stop", argv[0]))
				ft_apply(params, argv, ft_stop);
			else if (ft_strequ("exit", argv[0]))
				exit(0);
			else if (ft_strequ("reload", argv[0]))
				ft_reload(params->configfile);
			ft_printf_fd(msgsock, "end\n");
		}
		close(msgsock);
	}
}

void	ft_startup(t_app *app, t_params *params)
{
	if (app->autostart || app->starttime == 0)
		ft_start(app, params);
}

void	ft_daemon()
{
	if (!fork())
	{
		setsid();
		close(0);
		close(1);
		close(2);
		ft_printf_fd(1, "hahahah\n");
	}
	else
		exit(0);
}

int main(int argc, char **argv)
{
	t_jsobject *tokens;
	t_params	params;
	size_t		count;
	int			sockfd;

	if (argv[1])
	{
		ft_getter(&params);
		ft_init(&params);
		params.fd = 1;
		params.configfile = argv[1];
		ft_load_config_file(&params, argv[1]);
		ft_daemon();
		argv = ft_strsplit("0 all", ' ');
		ft_apply(&params, argv, ft_startup);
		sockfd = ft_init_socket();
		ft_loop(&params, sockfd);
	}
}
