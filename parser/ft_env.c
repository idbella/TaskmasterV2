/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:41:50 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/23 14:29:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_envtoarr(t_list *list)
{
	char	**env_str;
	t_env	*env;
	char	*entry;
	int		index;

	env = NULL;
	if (!(env_str = (char **)malloc(sizeof(char *) * ft_lstcount(list) + 1)))
		return (NULL);
	index = 0;
	while (list)
	{
		env = (t_env *)list->content;
		entry = ft_strjoin(env->key, "=");
		env_str[index] = ft_strjoin(entry, env->value);
		free(entry);
		list = list->next;
		index++;
	}
	env_str[index] = NULL;
	return (env_str);
}

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
	char		*kv[2];
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
			kv[0] = (char *)json_object_get_string(jsval);
			if (json_object_object_get_ex(j, "value", &jsval))
			{
				kv[1] = (char *)json_object_get_string(jsval);
				ft_addenv(app, kv[0], kv[1]);
			}
			else
				ft_printf_fd(1, "[!] key %s has no value\n", kv[0]);
		}
		i++;
	}
}
