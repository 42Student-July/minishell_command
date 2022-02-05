/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/05 13:46:10 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	t_exec_attr	*e_attr;

	init(&e_attr);
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
