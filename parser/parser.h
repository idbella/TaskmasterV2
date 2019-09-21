/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:09:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/21 14:42:16 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft/libft.h"
# include <fcntl.h>
# include "/Users/sid-bell/.brew/include/json-c/json.h"
# define REQ_OK 1
# define REQ_NO 0
# define _STRING_ 0
# define _INTEGER_ 1
# define _ARRAY_ 2

typedef struct json_object t_jsobject;

typedef struct s_entry
{
	char	*name;
	char	required;
	char	type;
}			   t_entry;

typedef struct s_env
{
	char	*key;
	char	*value;
}			   t_env;

typedef struct	s_app
{
	t_jsobject *data;
	char	*name;
	char	**argv;
	int	 	numprocs;
	mode_t  umask;
	char	*wdir;
	char	autostart;
	char	*autorestart;
	char	exitcode[256];
	int		startretries;
	int		starttime;
	char	stopsignal;
	int		stoptime;
	char	*stdout;
	char	*stderr;
	char	*stdin;
	t_list	*env;
}				t_app;

typedef struct s_params
{
	char	*jsontxt;
	t_list  *apps;
	t_list  *entrys;
}			   t_params;

void	ft_fill_entrys(t_params *params);
void	ft_load_info(t_params *params, t_app *js);
void	ft_getstring(t_app *app, t_entry *entry, t_jsobject *js);
void	ft_getinteger(t_app *app, t_entry *entry, t_jsobject *js);
void	ft_getarray(t_app *app, t_entry *entry, t_jsobject *js);
char	ft_isvalid(t_entry *entry, t_jsobject *js, enum json_type type);
void	ft_getenv(t_app *app, t_jsobject *js);
void	ft_addenv(t_app *app, char *key, char *value);
t_app	*ft_newapp(t_params *params, t_jsobject *js);
size_t	ft_loadjson(char *name, t_jsobject **js);
#endif
