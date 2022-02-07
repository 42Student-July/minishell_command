/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:01:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 13:35:27 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"


void	store_env(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_lst		*env_lst;
	t_content_f	f;
	bool		flag;

	f = print_kvs_debug;
	env_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		flag = ft_lstadd_back(&env_lst, \
		ft_lstnew(create_content_kvs(split[KEY], split[VALUE])));
		if (!flag)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		i++;
		free_split(split);
	}
	ea->env = env_lst;
}

void	print_env(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	printf("%s=%s\n", kvs->key, kvs->value);
}
