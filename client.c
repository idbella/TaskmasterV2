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
#include "read_line.h"

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

void		ft_initial_read_line(t_history **his, t_select **select)
{
	*his = ft_memalloc(sizeof(t_history));
	*select = ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	(*his)->history = ft_alloc_tab();
	(*his)->his_count = 0;
	ft_save_address(his, select);
}

int		main(int argc, char **argv)
{
	int			sock;
	char		*line;
	t_history	*his;
	t_select	*select;
	
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in seting Temcap parameters\n");
	ft_initial_read_line(&his, &select);
	sock = ft_init_sock(argv[1]);
	while (1)
	{
		ft_printf_fd(1, "$> ");
		if ((line = ft_read_line(his, select, 3)) != NULL)
		{
			ft_printf_fd(sock, "%s\n", line);
			if (ft_strequ("exit", line))
				exit(0);
			ft_stock_history(his->history, line, his->his_count);
			his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
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
