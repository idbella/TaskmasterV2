/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:35:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 12:40:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_getinteger(t_app *app, t_entry *entry, t_jsobject *js)
{
	int	intval;

	if (ft_isvalid(entry, js, json_type_int))
	{
		intval = json_object_get_int(js);
		if (ft_strequ(entry->name, "numprocs"))
			app->numprocs = intval;
		else if (ft_strequ(entry->name, "umask"))
			app->umask = intval;
		else if (ft_strequ(entry->name, "startretries"))
			app->startretries = intval;
		else if (ft_strequ(entry->name, "starttime"))
			app->starttime = intval;
		else if (ft_strequ(entry->name, "autostart"))
			app->autostart = intval;
	}
}
