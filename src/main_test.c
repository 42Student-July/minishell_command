/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 17:49:02 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	t_exec_attr *e_attr;

	e_attr = (t_exec_attr *)malloc(sizeof(t_exec_attr));
	if (e_attr == NULL)
		return (abort_minishell(MALLOC_ERROR, e_attr))
	if (is_self_cmd(argv[1]))
		execute_self(argc, argv, e_attr);
	else
	{
		command = create_builtin_cmd(argc, argv, &infile, &outfile);
		execute_builtin(command, environ);
	}

	return (0);
}
