/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:01:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 16:38:39 by mhirabay         ###   ########.fr       */
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

void	store_env(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**line;
	t_lst		*env_lst;
	t_content_f	f;
	bool		flag;

	f = print_kvs_debug;
	env_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		line = ft_split(environ[i], '=');
		if (line == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		flag = ft_lstadd_back(&env_lst, \
		ft_lstnew(create_content(line[KEY], line[VALUE])));
		if (!flag)
		{
			free_line(line);
			abort_minishell(MALLOC_ERROR, ea);
		}
		i++;
		free_line(line);
	}
	// ft_lstiter(env_lst, f);
	ea->env = env_lst;
}

void	print_env(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	printf("%s=%s\n", kvs->key, kvs->value);
}
