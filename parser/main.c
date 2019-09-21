/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:06:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 14:59:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void ft_print(t_app *app)
{
	t_env *e;

	ft_printf_fd(1, "name = %s\n", app->name);
	while (app->argv && *app->argv)
	{
		ft_printf_fd(1, "argv = %s\n", *app->argv);
		app->argv++;
	}
	while (app->env)
	{
		e = app->env->content;
		ft_printf_fd(1, "env :: %s=%s\n", e->key, e->value);
		app->env = app->env->next;
	}
	ft_printf_fd(1, "numprocs = %d\n", app->numprocs);
	ft_printf_fd(1, "umask = %d\n", app->umask);
	ft_printf_fd(1, "workingdir = %s\n", app->wdir);
	ft_printf_fd(1, "autorestart = %s\n", app->autorestart);
	ft_printf_fd(1, "startretries = %d\n", app->startretries);
	ft_printf_fd(1, "autostart = %d\n", app->autostart);
	ft_printf_fd(1, "starttime = %d\n", app->starttime);
	ft_printf_fd(1, "stoptime = %d\n", app->stoptime);
	ft_printf_fd(1, "stdout = %s\n", app->stdout);
	ft_printf_fd(1, "stderr = %s\n", app->stderr);
	ft_printf_fd(1, "stopsignal = %d\n", app->stopsignal);
	int i = 0;
	while (i < 256)
	{
		if (app->exitcode[i])
			ft_printf_fd(1, "exitcode : %d\n", i);
		i++;
	}
}

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
			ft_print(app);
		}
		i++;
	}
}

void	ft_init(t_params *params)
{
	params->entrys = NULL;
	params->apps = NULL;
	ft_fill_entrys(params);
}

int main(int argc, char **argv)
{
	t_jsobject *tokens;
	t_params	params;
	size_t		count;

	if (argv[1])
	{
		ft_init(&params);
		if ((count = ft_loadjson(argv[1], &tokens) > 0))
		{
			ft_loadapps(&params, tokens, count);
		}
	}
}