/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:24:01 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/05 10:25:15 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"
char	*create_export_value(char *key, char *value)
{
	// 合成して ex)declare -x key="value"を作る
	char 		*new_value;
	size_t		new_value_len;

	new_value_len = (EXPORT_CONST_LEN + ft_strlen(key) + ft_strlen(value) + NULL_CHAR);
	new_value = (char *)malloc(sizeof(char) * new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, "declare -x ", new_value_len);
	ft_strlcat(new_value, key, new_value_len);
	ft_strlcat(new_value, "=\"", new_value_len);
	ft_strlcat(new_value, value, new_value_len);
	ft_strlcat(new_value, "\"\n", new_value_len);
	return (new_value);
}

void	store_export(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**line;
	t_lst		*export_lst;
	t_content_f	f;
	bool		flag;
	char 		*value;

	f = print_kvs_debug;
	export_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		// exportはkeyはenvと同じだが、valueはdeclareも含めた一行にする。
		// TODO:envもだけど、=のあとが存在しなかったり、=がそもそもないケースが来ることも想定しておく。
		line = ft_split(environ[i], '=');
		if (line == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		value = create_export_value(line[KEY], line[VALUE]);
		if (value == NULL)
		{
			free_line(line);
			abort_minishell(MALLOC_ERROR, ea);
		}
		flag = ft_lstadd_back(&export_lst, \
		ft_lstnew(create_content_kvs(line[KEY], value)));
		if (!flag)
		{
			free_line(line);
			abort_minishell(MALLOC_ERROR, ea);
		}
		i++;
		free_line(line);
	}
	// ft_lstiter(export_lst, f);
	ea->export = export_lst;
}
