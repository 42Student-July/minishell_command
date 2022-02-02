/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 18:29:17 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	t_exec_attr	*e_attr;

	e_attr = (t_exec_attr *)malloc(sizeof(t_exec_attr));
	if (e_attr == NULL)
		abort_minishell(MALLOC_ERROR, e_attr);
	if (is_self_cmd(argv[1]))
		execute_self(argc, argv, e_attr);
	else
		execute_builtin(argc, argv, e_attr);

	return (0);
}
