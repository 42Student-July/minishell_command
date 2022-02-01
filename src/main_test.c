/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/01 13:25:34 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	execute_command(char *const *command, char *const *environ)
{
	// TODO: NULL判定などは未実装
	if (execve(command[0], command, environ) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, const char *argv[])
{
	char **environ;
	// char *av[10];

	(void)argc;
	// (void)argv;
	// av[0] = "/bin/echo";
	// av[1] = "hello";
	// av[2] = NULL;
	// av = argv;
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	execute_command((char *const *)argv, environ);
	return (0);
}
