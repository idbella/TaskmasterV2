/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_entrys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:04:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 00:21:18 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_addentry(t_params *params, char *name, char req, char type)
{
	t_entry *entry;
	t_list	*lst;

	entry = malloc(sizeof(t_entry));
	entry->name = name;
	entry->required = req;
	entry->type = type;
	lst = ft_lstnew(NULL, 0);
	lst->content = entry;
	ft_lstadd(&params->entrys, lst);
}

void	ft_fill_entrys(t_params *params)
{
	ft_addentry(params, "name", REQ_OK, _STRING_);
	ft_addentry(params, "cmd", REQ_OK, _STRING_);
	ft_addentry(params, "numprocs", REQ_NO, _INTEGER_);
	ft_addentry(params, "umask", REQ_NO, _INTEGER_);
	ft_addentry(params, "workingdir", REQ_NO, _STRING_);
	ft_addentry(params, "autostart", REQ_NO, _INTEGER_);
	ft_addentry(params, "autorestart", REQ_NO, _STRING_);
	ft_addentry(params, "exitcodes", REQ_NO, _ARRAY_);
	ft_addentry(params, "startretries", REQ_NO, _INTEGER_);
	ft_addentry(params, "starttime", REQ_NO, _INTEGER_);
	ft_addentry(params, "stopsignal", REQ_NO, _STRING_);
	ft_addentry(params, "stoptime", REQ_NO, _INTEGER_);
	ft_addentry(params, "stdout", REQ_NO, _STRING_);
	ft_addentry(params, "stderr", REQ_NO, _STRING_);
	ft_addentry(params, "env", REQ_NO, _ARRAY_);
}
