/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:24:01 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 11:05:36 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"
char	*create_export_value(char *value)
{
	// 合成して ex)declare -x key="value"を作る
	char 		*new_value;
	size_t		new_value_len;

	new_value_len = (ft_strlen(value) + DQUOTE + NULL_CHAR);
	new_value = (char *)malloc(sizeof(char) * new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, "\"", new_value_len);
	ft_strlcat(new_value, value, new_value_len);
	ft_strlcat(new_value, "\"", new_value_len);
	return (new_value);
}

// keyのasciiが一番小さい文字をとってくる
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
		// もし第２引数のほうが小さい値だった場合、tmpに入れる
		// その時strncmpの結果は0以上になる
		if (ft_strncmp(min_key, next_key, ft_strlen(min_key)) > 0)
		{
			tmp = lst->next;
		}

		lst = lst->next;
	}
	return (tmp);
}

bool	swap_content(t_lst *a, t_lst *b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return (false);
	if (a->content == b->content)
	{
		printf("onajiyatu\n");
		return (true);
	}
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (true);
}


void	sort_ascii(t_lst **export_lst)
{
	// 大文字アルファベット → _ → 小文字のアルファベットに並び替える
	t_lst	*min;
	size_t	len;
	size_t	i;
	t_lst	*tmp;

	i = 0;
	len = ft_lstsize(*export_lst);
	tmp = *export_lst;
	while (tmp->next != NULL)
	{
		min = get_min_lst(tmp);
		// ft_lstswap(export_lst, &min);
		
		// sortがおわったらnextの値も変えないとだめ
		// lstの構造を変えるのはめんどくさそうなので、contentだけ入れ替えるようにする。
		swap_content(tmp, min);
		tmp = tmp->next;
	}
	// print_all_export_lst(*export_lst);
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
		line = ft_split(environ[i], '=');
		if (line == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		value = create_export_value(line[VALUE]);
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
	sort_ascii(&export_lst);
	// ft_lstiter(export_lst, f);
	ea->export = export_lst;
}

void	print_export_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	printf("declare -x %s=%s\n", kvs->key, kvs->value);
}


