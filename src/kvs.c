/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:43:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 13:26:08 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	free_all_kvs(t_kvs *kvs)
{
	if (kvs != NULL)
	{
		if (kvs->key != NULL)
			free(kvs->key);
		if (kvs->value != NULL)
			free(kvs->value);
		free(kvs);
	}
}

char	*get_key(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	return (kvs->key);
}

char	*get_value(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	return (kvs->value);
}

t_lst	*get_min_lst(t_lst *lst)
{
	t_lst	*tmp;
	char	*min_key;
	char	*next_key;

	tmp = lst;
	while (lst->next != NULL)
	{
		min_key = get_key(tmp->content);
		next_key = get_key(lst->next->content);
		// lvalueの方が大きいので、tmpをrvalueにchange
		if (ft_strncmp(min_key, next_key, ft_strlen(min_key)) > 0)
		{
			tmp = lst->next;
		}
		lst = lst->next;
	}
	return (tmp);
}


void	*create_content_kvs(char *key, char *value)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)malloc(sizeof(t_kvs));
	if (kvs == NULL)
		return (NULL);
	kvs->key = ft_strdup(key);
	if (kvs->key == NULL)
		return (NULL);
	kvs->value = ft_strdup(value);
	if (kvs->value == NULL)
	{
		free(kvs->key);
		return (NULL);
	}
	return ((void *)kvs);
}