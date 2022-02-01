/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/01 11:13:27 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, char *const argv[])
{
	char **environ;
	char *av[10];

	(void)argc;
	(void)argv;
	av[0] = "/bin/echo";
	av[1] = "hello";
	av[2] = NULL;
	// av = argv;
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	if (execve(av[0], av, environ) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
	}
	return (0);
}
