/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/01 10:47:13 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, char *const argv[])
{
	char **environ;
	// char *const *av;

	(void)argc;
	// argv[0] = "echo";
	// argv[1] = "Hello World!";
	// argv[2] = NULL;

	// av = argv;
	// 第一引数
	execve("/bin/sh", argv, environ);
	
	return (0);
}
