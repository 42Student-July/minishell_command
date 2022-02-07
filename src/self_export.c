/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:53:41 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 15:06:41 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// 新しく追加
bool	lstadd_sort_ascii(t_lst **export_lst, char **arg)
{
	// まずadd_backでポインタの位置を確定した後、contentを入れ替える
	bool	flag;

	flag = ft_lstadd_back(export_lst, \
			ft_lstnew(create_content_kvs(arg[KEY], arg[VALUE])));
	if (!flag)
		return (false);
	sort_ascii(export_lst);
	return (true);
}

void	export_with_args(t_exec_attr *ea)
{
	char		**arg;
	bool		flag;

	if (ea->command[CMD_ARG] != NULL)
	{
		arg = ft_split(ea->command[CMD_ARG], '=');
		if (arg == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		flag = ft_lstadd_back(&ea->env, \
			ft_lstnew(create_content_kvs(arg[KEY], arg[VALUE])));
		if (!flag)
			abort_minishell_with(MALLOC_ERROR, ea, arg);
		if (!lstadd_sort_ascii(&ea->export, arg))
			abort_minishell_with(MALLOC_ERROR, ea, arg);
	}
	print_all_env_lst(ea->env);
	print_all_export_lst(ea->export);
}

void	export_no_args(t_exec_attr *ea)
{
	print_all_export_lst(ea->export);
}

void	exec_self_export(t_exec_attr *ea)
{

	if (ea->command[CMD_ARG] == NULL)
		export_no_args(ea);
	else
		export_with_args(ea);
}
