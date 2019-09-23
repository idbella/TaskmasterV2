#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define NAME "SOCK"
#include <stdio.h>
#include <pthread.h>

int	ft_init_sock(char *argv)
{
	int					sock;
	struct sockaddr_un	server;
	char				*file;

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
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("opening stream socket");
		exit(1);
	}
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, file);
	if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0)
	{
		close(sock);
		perror("connecting stream socket");
		exit(1);
	}
	return (sock);
}

int		main(int argc, char **argv)
{
	int			sock;
	char		*line;

	sock = ft_init_sock(argv[1]);
	while (1)
	{
		ft_printf_fd(1, "$> ");
		if (get_next_line(0, &line))
		{
			ft_printf_fd(sock, "%s\n", line);
			if (ft_strequ("exit", line))
				exit(0);
			while (get_next_line(sock, &line))
			{
				if (ft_strequ(line, "end"))
					break ;
				ft_printf_fd(1, "%s\n", line);
			}
		}
	}
	close(sock);
}
