/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:43:17 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 10:48:23 by mhirabay         ###   ########.fr       */
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

void	*create_kvs_content(char *key, char *value)
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

void	*free_char_double_ptr(char **column)
{
	size_t	i;

	i = 0;
	if (column != NULL)
	{
		while (column[i] != NULL)
		{
			free(column[i]);
		}
		free(column);
	}
	return (NULL);
}

char	*create_environ_line(char *key, char *value, bool is_end)
{
	size_t	key_size;
	size_t	value_size;
	size_t	line_size;
	char	*line;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	line_size = key_size + EQUAL + value_size + LF;
	line = (char *)malloc(sizeof(char) * line_size);
	if (line == NULL)
		return (NULL);
	ft_strlcat(line, key, line_size);
	ft_strlcat(line, "=", line_size);
	ft_strlcat(line, value, line_size);
	if (is_end)
		ft_strlcat(line, "\n", line_size);
	else
		ft_strlcat(line, "\0", line_size);
	return (line);
}

char	**convert_to_array(t_lst *lst)
{
	char	**array;
	size_t	lst_size;
	size_t	i;

	i = 0;
	lst_size = ft_lstsize(lst);
	array = (char **)malloc(sizeof(char *) * (lst_size + NULL_CHAR));
	if (array == NULL)
		return (NULL);
	while (i < lst_size)
	{
		//　TODO: 行数長くなっちゃうからget_keyの引数はlstでもいいのかも
		array[i] = create_environ_line(\
			get_key(lst->content), get_value(lst->content), false);
		if (array[i] == NULL)
			return (free_char_double_ptr(array));
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	// print_array(array);
	return (array);
}
