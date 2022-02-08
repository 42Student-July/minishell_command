/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:43:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/08 11:07:08 by mhirabay         ###   ########.fr       */
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

bool	is_lvalue_bigger_ascii(char *lvalue, char *rvalue)
{
	size_t	llen;
	size_t	rlen;
	size_t	use_len;

	llen = ft_strlen(lvalue);
	rlen = ft_strlen(rvalue);
	if (llen > rlen)
		use_len = llen;
	else
		use_len = rlen;
	if (ft_strncmp(lvalue, rvalue, use_len) > 0)
		return (true);
	return (false);
}


t_lst	*get_min_key(t_lst *lst)
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
		if (is_lvalue_bigger_ascii(min_key, next_key))
			tmp = lst->next;
		lst = lst->next;
	}
	return (tmp);
}

bool	is_same_key(char *a, char *b)
{
	if (ft_strlen(a) != ft_strlen(b))
		return (false);
	if (ft_strncmp(a, b, ft_strlen(a)) != 0)
		return (false);
	return (true);
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
	// export k のような形で入る場合を考慮して、valueはnullを許容する
	if (value != NULL)
	{
		kvs->value = ft_strdup(value);
		if (kvs->value == NULL)
		{
			free(kvs->key);
			return (NULL);
		}
	}
	else
	{
		printf("value NULL\n");
		kvs->value = NULL;
	}
	return ((void *)kvs);
}
