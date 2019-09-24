/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:44:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:19:51 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_connect_socket(char *file, int socket_fd)
{
	struct sockaddr_un	server;
	struct sockaddr		*address;

	address = (struct sockaddr *)&server;
	server.sun_family = AF_UNIX;
	ft_strcpy(server.sun_path, file);
	if (connect(socket_fd, address, sizeof(server)) < 0)
	{
		close(socket_fd);
		ft_printf_fd(1, "run ./taskmasterd first\n");
		perror("connecting stream socket");
		exit(1);
	}
}

int		ft_init_sock(char *argv)
{
	int		socket_fd;
	char	*file;

	file = NAME;
	if (!argv && access(file, F_OK))
	{
		ft_printf_fd(1, "SOCK socket file not found run ./taskamsterctl path_to_socket_file\n");
		exit(0);
	}
	else if (argv)
		file = argv;
	if (access(file, F_OK))
	{
		ft_printf_fd(1, "%s no such file or directory\n", file);
		exit(0);
	}
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		perror("opening stream socket");
		exit(1);
	}
	ft_connect_socket(file, socket_fd);
	return (socket_fd);
}
