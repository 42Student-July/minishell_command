/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 17:03:23 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;

	environ = NULL;
	if (is_self_cmd(argv[1]))
	{
		command = create_self_cmd(argc, argv);
		execute_self(command, environ);
	}
	else
	{
		command = create_builtin_cmd(argc, argv);
		execute_builtin(command, environ);
	}

	return (0);
}
