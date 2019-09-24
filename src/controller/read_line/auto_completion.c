/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:31:48 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/19 13:31:50 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	*ft_complete_thename(char *s)
{
	char *begin;

	if (ft_strlen(s) == 0)
		return (NULL);
	if (!(begin = ft_strrchr(s, ' ')))
		return (ft_strdup(s));
	return (ft_strdup(begin + 1));
}

char	ft_looks_like(char *name, char *begin)
{
	int len;

	len = ft_strlen(begin);
	if ((int)ft_strlen(name) <= len)
		return (0);
	if (!ft_strncmp(name, begin, len))
		return (len);
	return (0);
}

char	*ft_search_in(char *begin)
{
	char **tb;
	int j;
	int ret;
	char	*r;

	tb = ft_strsplit("start stop restart status reload", ' ');
	j = 0;
	while (tb[j])
	{
		if ((ret = ft_looks_like(tb[j], begin)) > 0)
		{
			r = ft_strdup(tb[j] + ret);
			ft_free_tab(tb);
			return (r);
		}
		j++;
	}
	ft_free_tab(tb);
	return (NULL);
}

char	*ft_auto_completion(t_cursor *pos, char *s)
{
	char	*begin;
	char	*complete;
	char	*new;
	int		len;

	if (pos->index != (int)ft_strlen(s) || !(begin = ft_complete_thename(s)))
		return (s);
	if (!(complete = ft_search_in(begin)))
		return (s);
	len = ft_strlen(complete);
	ft_putstr_term(pos->num_col, complete, pos);
	new = ft_strfreejoin(s, complete);
	ft_get_end_of_line_pos(pos, new, pos->num_col);
	ft_get_new_pos(pos, len);
	pos->index += len;
	ft_strdel(&begin);
	return (new);
}
