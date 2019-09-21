/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_invalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:48:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 01:49:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	ft_isvalid(t_entry *entry, t_jsobject *js, enum json_type type)
{
	int b;

	b = 0;
	if (ft_strequ(entry->name, "autostart")
		&& json_object_get_type(js) == json_type_boolean)
		return (1);
	if (json_object_get_type(js) != type)
	{
		if (entry->required)
		{
			ft_printf_fd(2, "required field %s has an invalid datatype\n",
				entry->name);
			exit(1);
		}
		ft_printf_fd(2, "[!] field %s has an invalid datatype\n",
			entry->name);
		return (0);
	}
	return (1);
}
