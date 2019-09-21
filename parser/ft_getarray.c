/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:35:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 14:47:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_getexcode(t_app *app, t_jsobject *js)
{
	int			excode;
	size_t		len;
	int			i;
	t_jsobject	*j;

	len = json_object_array_length(js);
	i = 0;
	while (i < len)
	{
		j = json_object_array_get_idx(js, i);
		if (json_object_get_type(j) == json_type_int)
		{
			excode = json_object_get_int(j);
			if (excode < 0 || excode > 255)
				ft_printf_fd(2, "[!] invalid exit code %d\n", excode);
			else
				app->exitcode[excode] = 1;
		}
		i++;
	}
}

void	ft_getarray(t_app *app, t_entry *entry, t_jsobject *js)
{
	char		*key;
	char		*value;
	t_jsobject	*jsval;

	if (ft_isvalid(entry, js, json_type_array))
	{
		if (ft_strequ(entry->name, "env"))
			ft_getenv(app, js);
		else if (ft_strequ(entry->name, "exitcodes"))
			ft_getexcode(app, js);
	}
}
