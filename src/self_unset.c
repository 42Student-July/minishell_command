/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:19:55 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/08 11:09:07 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	del_content(t_lst *lst, char *key)
{
	t_lst	*tmp;

	tmp = get_lst_by_key(lst, key);
	// printf("get_key(tmp->content) : %s\n", get_key(tmp->content));
	ft_lstdel(lst, tmp);
}


void	exec_self_unset(t_exec_attr *ea)
{
	// envlstとexportlstから対象の文字列を削除
	if (ea->command[CMD_ARG] == NULL)
		return ;
	if (is_invalid_name(ea->command[CMD_ARG]))
		print_error_msg_with_var(UNSET, ea->command[CMD_ARG]);
	del_content(ea->env, ea->command[CMD_ARG]);
	del_content(ea->export, ea->command[CMD_ARG]);
}

