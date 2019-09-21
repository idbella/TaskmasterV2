/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:41:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 12:42:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_addenv(t_app *app, char *key, char *value)
{
	t_env	*env;
	t_list	*node;

	env = malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	node = ft_lstnew(NULL, 0);
	node->content = env;
	ft_lstadd(&app->env, node);
}

void	ft_getenv(t_app *app, t_jsobject *js)
{
	char		*key;
	char		*value;
	t_jsobject	*jsval;
	size_t		len;
	int			i;
	t_jsobject	*j;

	len = json_object_array_length(js);
	i = 0;
	while (i < len)
	{
		j = json_object_array_get_idx(js, i);
		if (json_object_object_get_ex(j, "key", &jsval))
		{
			key = (char *)json_object_get_string(jsval);
			if (json_object_object_get_ex(j, "value", &jsval))
			{
				value = (char *)json_object_get_string(jsval);
				ft_addenv(app, key, value);
			}
			else
				ft_printf_fd(1, "[!] key %s has no value\n", key);
		}
		i++;
	}
}
