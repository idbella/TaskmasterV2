/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadjson.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:27:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 19:56:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	ft_parse(char *text, t_jsobject **tokens)
{
	size_t		count;

	count = 0;
	if (!(*tokens = json_tokener_parse(text)))
	{
		ft_printf_fd(1, "error parsing json file\n");
		return (0);
	}
	count = json_object_array_length(*tokens);
	return (count);
}

char	*ft_read(int fd)
{
	char	*line;
	char	*tmp;
	char	*txt;

	txt = ft_strnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = txt;
		txt = ft_strjoin(txt, line);
		free(tmp);
		free(line);
		line = NULL;
	}
	return (txt);
}

size_t	ft_loadjson(char *name, t_jsobject **js)
{
	int		fd;
	char	*txt;
	size_t	count;

	count = 0;
	if ((fd = open(name, O_RDONLY)) > 0)
	{
		txt = ft_read(fd);
		close(fd);
		count = ft_parse(txt, js);
		free(txt);
	}
	else
	{
		ft_printf_fd(1, "[!] cannot open file %s\n", name);
		exit(1);
	}
	return (count);
}
