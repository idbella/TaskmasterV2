/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 06:27:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/07/11 21:56:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_endl(char *str)
{
	ssize_t pos;

	pos = 0;
	while (*str)
	{
		if (*str == '\n')
			return (pos);
		str++;
		pos++;
	}
	return (-1);
}

static int		ft_adjust(char **line, char **array, int pos)
{
	char *tmp;

	if (pos >= 0)
	{
		tmp = *line;
		*line = ft_strsub(*array, 0, pos);
		if (tmp)
			free(tmp);
		tmp = *array;
		*array = ft_strdup(*array + pos + 1);
		free(tmp);
	}
	else
	{
		tmp = *line;
		*line = *array;
		if (tmp)
			free(tmp);
		if (!**array)
		{
			*line = NULL;
			return (0);
		}
		if (*array)
			free(*array);
		*array = NULL;
		return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char *array;
	ssize_t		lenght;
	ssize_t		pos;
	char		buff_test[1];
	char		*tmp;

	if (fd < 0 || !line || fd > 4863 || read(fd, buff_test, 0) < 0)
		return (-1);
	if (!array)
		array = ft_strnew(1);
	if ((pos = ft_endl(array)) == -1)
	{
		if (!(*line = ft_strnew(BUFF_SIZE)))
			return (-1);
		while ((lenght = read(fd, *line, BUFF_SIZE)) > 0)
		{
			(*line)[lenght] = '\0';
			tmp = array;
			array = ft_strjoin(array, *line);
			free(tmp);
			if ((pos = ft_endl(array)) >= 0)
				break ;
		}
		if (lenght < 0)
			return (-1);
	}
	return (ft_adjust(line, &array, pos));
}
