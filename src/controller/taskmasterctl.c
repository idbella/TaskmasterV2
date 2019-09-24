/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskmasterctl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:44:40 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:46:43 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

char	ft_isbuiltin(char *str)
{
	char	**argv;
	char	*tmp;

	argv = ft_strsplit(str, ' ');
	if (argv && argv[0])
	{
		if (ft_strequ("status", argv[0]))
			return (1);
		if (ft_strequ("exit", argv[0]))
			return (1);
		else if (ft_strequ("start", argv[0]))
			return (1);
		else if (ft_strequ("restart", argv[0]))
			return (1);
		else if (ft_strequ("stop", argv[0]))
			return (1);
		else if (ft_strequ("reload", argv[0]))
			return (1);
	}
	else
		return (0);
	ft_printf_fd(1, "%s not a valid command\n", argv[0]);
	return (0);
}

void	ft_initial_read_line(t_history **his, t_select **select)
{
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in seting Temcap parameters\n");
	*his = ft_memalloc(sizeof(t_history));
	*select = ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	(*his)->history = ft_alloc_tab();
	(*his)->his_count = 0;
	ft_save_address(his, select);
}

char	*ft_readline(t_select *select, t_history *his)
{
	char	*line;

	if ((line = ft_read_line(his, select, 3)) != NULL)
	{
		ft_stock_history(his->history, line, his->his_count);
		his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
	}
	return (line);
}

int		main(int argc, char **argv)
{
	int			sock;
	char		*line;
	t_history	*his;
	t_select	*select;

	ft_initial_read_line(&his, &select);
	sock = ft_init_sock(argv[1]);
	while (1)
	{
		ft_printf_fd(1, "$> ");
		if ((line = ft_readline(select, his)))
		{
			if (!ft_isbuiltin(line))
				continue ;
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
