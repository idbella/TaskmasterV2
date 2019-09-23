/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:22:06 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 15:35:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft__getstr(t_jsobject *js, char *key)
{
	json_object	*val;
	char		*strval;

	if (!json_object_object_get_ex(js, key, &val))
		return (NULL);
	strval = (char *)json_object_get_string(val);
	return (strval);
}

int		ft__getint(t_jsobject *js, char *key)
{
	json_object	*val;
	int			intval;

	if (!json_object_object_get_ex(js, key, &val))
		return (0);
	intval = json_object_get_int(val);
	return (intval);
}

char	ft_sigstr(char *sig)
{
	t_jsobject	*tokens;
	size_t		count;
	char		*signame;
	json_object	*tok;
	int			sigval;

	if ((count = ft_loadjson("parser/signals.json", &tokens)))
	{
		while (count-- > 0)
		{
			tok = json_object_array_get_idx(tokens, count);
			if (ft_strequ(ft__getstr(tok, "name"), sig))
				return (ft__getint(tok, "id"));
		}
	}
	return (0);
}
