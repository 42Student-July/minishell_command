/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:36:05 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 10:48:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// TODO:引数あるバージョンは未対応
void	exec_self_env(t_exec_attr *ea)
{
	print_all_env_lst(ea);
}

void	store_env(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_lst		*env_lst;
	bool		flag;

	env_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		flag = ft_lstadd_back(&env_lst, \
		ft_lstnew(create_kvs_content(split[KEY], split[VALUE])));
		if (!flag)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		i++;
		free_split(split);
	}
	ea->env = env_lst;
}

void	print_all_env_lst(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_env_kvs;
	ft_lstiter(ea->env, f);
}


void	print_env_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	if (kvs->value == NULL)
		printf("%s=\n", kvs->key);
	else
		printf("%s=%s\n", kvs->key, kvs->value);
}
