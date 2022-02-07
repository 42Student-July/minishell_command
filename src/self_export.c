/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:53:41 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/05 13:21:40 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	export_with_args(t_exec_attr *ea)
{
	char		**arg;
	bool		flag;
	t_content_f	f;

	f = print_export;
	if (ea->command[CMD_ARG] != NULL)
	{
		arg = ft_split(ea->command[CMD_ARG], '=');
		if (arg == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		flag = ft_lstadd_back(&ea->env, \
			ft_lstnew(create_content_kvs(arg[KEY], arg[VALUE])));
		if (!flag)
		{
			free_line(arg);
			abort_minishell(MALLOC_ERROR, ea);
		}
	}
}

void	export_no_args(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_export;
	ft_lstiter(ea->export, f);
}

void	exec_self_export(t_exec_attr *ea)
{

	if (ea->command[CMD_ARG] == NULL)
		export_no_args(ea);
	else
		export_with_args(ea);
}