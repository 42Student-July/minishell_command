/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:24:01 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 21:54:44 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	free_line(char **line)
{
	size_t	i;

	i = 0;
	if (line != NULL)
	{
		while (line[i] != NULL)
		{
			free(line[i]);
			i++;
		}
		free(line);
	}
}

void	create_export_value(char *env, char *key, char *value)
{
	// 合成して ex)declare -x key="value"を作る
	const char	*prefix;
	const char	*dquote;
	char 		*new_value;

	prefix = "declare -x ";
	dquote = "\"";
	// strlcatの方がfreeとmallocのエラーハンドリングしなくていいからそっちで実装する。
	new_value = ft_strjoin(prefix, key);
	new_value = ft_strjoin(new_value, "=\"");
	new_value = ft_strjoin(new_value, value);
	new_value = ft_strjoin(new_value, "\"\n");
}

void	store_export(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**line;
	t_lst		*export_lst;
	t_content_f	f;
	bool		flag;

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
		create_export_value(environ[i], line[KEY], line[VALUE]);
		flag = ft_lstadd_back(&export_lst, \
		ft_lstnew(create_content_kvs(line[KEY], line[VALUE])));
		if (!flag)
		{
			free_line(line);
			abort_minishell(MALLOC_ERROR, ea);
		}
		i++;
		free_line(line);
	}
	// ft_lstiter(env_lst, f);
	ea->export = export_lst;
}

void	print_env(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	printf("%s=%s\n", kvs->key, kvs->value);
}
