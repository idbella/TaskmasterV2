/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmasterd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:06:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:39:37 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_init_d(t_params *params)
{
	params->logfile = open("log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	params->entrys = NULL;
	params->apps = NULL;
	ft_fill_entrys(params);
	signal(SIGCHLD, ft_sigchild);
	ft_printf_fd(params->logfile,
		"%s starting taskamster daemon with config file %s\n",
		ft_gettime(),
		params->configfile);
}

int		ft_init_socket(void)
{
	int					sock;
	struct sockaddr_un	server;

	if (!access(NAME, F_OK))
		remove(NAME);
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	server.sun_family = AF_UNIX;
	ft_strcpy(server.sun_path, NAME);
	bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un));
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
			ft_eval(params, argv);
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
	ft_printf_fd(1, "taskamster daemon started\n");
	if (!fork())
	{
		setsid();
		close(0);
		close(1);
		close(2);
	}
	else
		exit(0);
}

int		main(int argc, char **argv)
{
	t_jsobject	*tokens;
	t_params	params;
	size_t		count;
	int			sockfd;

	if (argv[1])
	{
		ft_getter(&params);
		params.configfile = argv[1];
		ft_init_d(&params);
		params.fd = 1;
		ft_load_config_file(&params, argv[1]);
		ft_daemon();
		argv = ft_strsplit("0 all", ' ');
		ft_apply(&params, argv, ft_startup);
		sockfd = ft_init_socket();
		ft_loop(&params, sockfd);
	}
	else
		ft_printf_fd(1, "usage ./taskmasterd configfile.json\n");
}
