/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 15:04:29 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	extern char	**environ;
	t_exec_attr	*e_attr;

	e_attr = (t_exec_attr *)malloc(sizeof(t_exec_attr));
	if (e_attr == NULL)
		abort_minishell(MALLOC_ERROR, e_attr);
	store_env(e_attr, environ);
	if (is_self_cmd(argv[1]))
	{
		create_self_cmd_from_arg(argc, argv, e_attr);
		execute_self(e_attr);
	}
	else
	{
		create_builtin_cmd_from_arg(argc, argv, e_attr);
		execute_builtin(e_attr);
	}
	return (0);
}
