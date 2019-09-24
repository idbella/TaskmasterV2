

#include "read_line.h"

char		*ft_strfreejoin(char *s1, char *s2)
{
	char			*result;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	if ((result = malloc(len + ft_strlen(s2) + 1)))
	{
		ft_strcpy(result, s1);
		ft_strcpy(result + len, s2);
	}
	free(s1);
	free(s2);
	return (result);
}

char	*ft_strjoir(char *s1, char *s2, int rm)
{
	char		*new_str;
	size_t		j;
	size_t		i;
	size_t		s1_len;
	size_t		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_strnew(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	while (++j < s2_len)
		*(new_str + i++) = *(s2 + j);
	if (rm == 1 || rm == 3)
		ft_strdel(&s1);
	if (rm == 2 || rm == 3)
		ft_strdel(&s2);
	return (new_str);
}

int		ft_find_char(char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void		ft_err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void		ft_save_address(t_history **his, t_select **select)
{
	static t_history	*p_his;
	static t_select		*p_select;

	if (*his != NULL && *select != NULL)
	{
		p_his = *his;
		p_select = *select;
	}
	else
	{
		*his = p_his;
		*select = p_select;
	}
}