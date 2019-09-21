/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadjson.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:27:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 14:57:23 by sid-bell         ###   ########.fr       */
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

size_t	ft_loadjson(char *name, t_jsobject **js)
{
	int		fd;
	char	*txt;
	char	*line;
	char	*tmp;
	size_t	count;

	count = 0;
	if ((fd = open(name, O_RDONLY)) > 0)
	{
		txt = ft_strnew(0);
		while (get_next_line(fd, &line) > 0)
		{
			tmp = txt;
			txt = ft_strjoin(txt, line);
			free(tmp);
			free(line);
			line = NULL;
		}
		close(fd);
		count = ft_parse(txt, js);
		free(txt);
	}
	else
		ft_printf_fd(1, "cannot open file %s\n", name);
	return (count);
}
