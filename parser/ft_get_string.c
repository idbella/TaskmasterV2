/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:28:38 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 23:08:45 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_getstring(t_app *app, t_entry *entry, t_jsobject *js)
{
	char	*strval;

	if (ft_isvalid(entry, js, json_type_string))
	{
		strval = (char *)json_object_get_string(js);
		if (ft_strequ(entry->name, "name"))
			app->name = strval;
		if (ft_strequ(entry->name, "cmd"))
		{
			app->argv = ft_strsplit(strval, ' ');
			if (app->argv && app->argv[0] && app->argv[0][0] != '/')
			{
				ft_printf_fd(1, "[!] Error : command %s must have an absolute path\n", app->argv[0]);
				exit(0);
			}
		}
		if (ft_strequ(entry->name, "workingdir"))
			app->wdir = strval;
		if (ft_strequ(entry->name, "workingdir"))
			app->wdir = strval;
		if (ft_strequ(entry->name, "autorestart"))
			app->autorestart = strval;
		if (ft_strequ(entry->name, "stopsignal"))
			app->stopsignal = ft_sigstr(strval);
		if (ft_strequ(entry->name, "stdout"))
			app->std_out = strval;
		if (ft_strequ(entry->name, "stderr"))
			app->std_err = strval;
	}
}
