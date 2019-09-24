/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadconfig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:06:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/24 20:42:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_loadapps(t_params *params, t_jsobject *tokens, size_t count)
{
	int			i;
	t_jsobject	*js;
	t_app		*app;

	i = 0;
	while (i < count)
	{
		if ((js = json_object_array_get_idx(tokens, i)))
		{
			app = ft_newapp(params, js);
			ft_load_info(params, app);
		}
		i++;
	}
}

char	*ft_gettime(void)
{
	char		*t;
	time_t		tmp;
	int			i;

	time(&tmp);
	t = ctime(&tmp);
	i = 0;
	while (t && t[i])
	{
		if (t[i] == '\n')
			t[i] = '\0';
		i++;
	}
	return (t);
}

void	ft_load_config_file(t_params *params, char *file)
{
	t_jsobject	*tokens;
	size_t		count;

	if ((count = ft_loadjson(file, &tokens)) > 0)
		ft_loadapps(params, tokens, count);
	else
		ft_printf_fd(params->logfile,
			"[%s]\t configuration file %s contains nothing\n",
				ft_gettime(), params->logfile);
}
