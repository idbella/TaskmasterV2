/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadfromjs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:29:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 00:47:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_load_info(t_params *params, t_app *app)
{
	t_jsobject	*name;
	char		*strval;
	t_list		*lst;
	t_entry		*entry;

	lst = params->entrys;
	while (lst)
	{
		entry = lst->content;
		if (json_object_object_get_ex(app->data, entry->name, &name))
		{
			if (entry->type == _STRING_)
				ft_getstring(app, entry, name);
			else if (entry->type == _INTEGER_)
				ft_getinteger(app, entry, name);
			else if (entry->type == _ARRAY_)
				ft_getarray(app, entry, name);
		}
		else if (entry->required)
		{
			ft_printf_fd(1, "error loading required flied %s\n", entry->name);
			exit(1);
		}
		lst = lst->next;
	}
}
