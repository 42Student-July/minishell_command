/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 14:43:34 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;
	int			command_num;

	environ = NULL;
	command_num = argc;
	if (is_self_cmd(argv[1]))
		execute_self(argv, environ);
	else
	{
		command = create_builtin_cmd(command_num, argv);
		execute_builtin(command, environ);
	}
	return (0);
}
