/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:24:01 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 18:03:10 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"
char	*create_export_value(char *value)
{
	// 合成して ex)declare -x key="value"を作る
	char 		*new_value;
	size_t		new_value_len;
	size_t		value_len;

	if (value == NULL)
		value_len = 0;
	else
		value_len = ft_strlen(value);
	new_value_len = (value_len + DQUOTE + NULL_CHAR);
	new_value = (char *)malloc(sizeof(char) * new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, "\"", new_value_len);
	ft_strlcat(new_value, value, new_value_len);
	ft_strlcat(new_value, "\"", new_value_len);
	return (new_value);
}

void	sort_ascii(t_lst **export_lst)
{
	// 大文字アルファベット → _ → 小文字のアルファベットに並び替える
	t_lst	*min;
	t_lst	*tmp;

	tmp = *export_lst;
	while (tmp->next != NULL)
	{
		min = get_min_key(tmp);
		swap_content(tmp, min);
		tmp = tmp->next;
	}
}

void	print_all_export_lst(t_lst *export_lst)
{
	t_content_f	f;

	f = print_export_kvs;
	ft_lstiter(export_lst, f);
}

void	store_export(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_lst		*export_lst;
	bool		flag;
	char		*value;

	export_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		value = create_export_value(split[VALUE]);
		if (value == NULL)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		flag = ft_lstadd_back(&export_lst, \
		ft_lstnew(create_content_kvs(split[KEY], value)));
		if (!flag)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		i++;
		free_split(split);
	}
	sort_ascii(&export_lst);
	ea->export = export_lst;
}

void	print_export_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	if (kvs->value == NULL)
		printf("declare -x %s\n", kvs->key);
	else
		printf("declare -x %s=%s\n", kvs->key, kvs->value);
}
