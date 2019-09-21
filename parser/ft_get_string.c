/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:28:38 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 14:58:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	ft_sigstr(char *sig)
{
	t_jsobject	*tokens;
	size_t		count;
	char		*signame;
	json_object	*tok;
	json_object	*val;
	int			sigval;

	if ((count = ft_loadjson("signals.json", &tokens)))
	{
		while (count-- > 0)
		{
			tok = json_object_array_get_idx(tokens, count);
			json_object_object_get_ex(tok, "name", &val);
			signame = (char *)json_object_get_string(val);
			if (ft_strequ(signame, sig))
			{
				json_object_object_get_ex(tok, "id", &val);
				sigval = json_object_get_int(val);
				return (sigval);
			}
		}
	}
	return (0);
}

void	ft_getstring(t_app *app, t_entry *entry, t_jsobject *js)
{
	char	*strval;

	if (ft_isvalid(entry, js, json_type_string))
	{
		strval = (char *)json_object_get_string(js);
		if (ft_strequ(entry->name, "name"))
			app->name = strval;
		if (ft_strequ(entry->name, "cmd"))
			app->argv = ft_strsplit(strval, ' ');
		if (ft_strequ(entry->name, "workingdir"))
			app->wdir = strval;
		if (ft_strequ(entry->name, "workingdir"))
			app->wdir = strval;
		if (ft_strequ(entry->name, "autorestart"))
			app->autorestart = strval;
		if (ft_strequ(entry->name, "stopsignal"))
			app->stopsignal = ft_sigstr(strval);
		if (ft_strequ(entry->name, "stdout"))
			app->stdout = strval;
		if (ft_strequ(entry->name, "stderr"))
			app->stderr = strval;
		if (ft_strequ(entry->name, "stdin"))
			app->stdin = strval;
	}
}
