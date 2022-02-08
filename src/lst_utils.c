/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:27:06 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/08 11:05:05 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

bool	swap_content(t_lst *a, t_lst *b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return (false);
	if (a->content == b->content)
	{
		return (true);
	}
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (true);
}

t_lst	*get_lst_by_key(t_lst *lst, char *key)
{
	t_lst	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (is_same_key(get_key(ret->content), key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}
