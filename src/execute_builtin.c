/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 15:11:59 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	execute_builtin(char *const *command, char **environ)
{
	pid_t	pid;
	int		status;
	pid_t	error_num;

	pid = fork();
	if (pid == -1)
	{
		printf("Error\n");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("ch\n");
		x_execve(command, environ);
	}
	else
	{
		printf("parent\n");
		error_num = wait(&status);
		if (pid == -1)
		{
			printf("Error\n");
			exit(1);
		}
	}
}

void	x_execve(char *const *command, char *const *environ)
{
	// TODO: NULL判定などは未実装
	if (execve(command[CMD_NAME], command, environ) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

bool	is_not_exec_path(const char *command)
{
	size_t	i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (false);
		i++;
	}
	return (true);
}

char *const	*create_builtin_cmd(int argc, const char *argv[])
{
	int		i;
	char	*bin_path;
	char	**command;

	i = 0;
	bin_path = "/bin/";
	// argv[0]は実行コマンドなんで、なくす。
	// 最後のNULL止めのために+1する。
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (is_not_exec_path(argv[1]))
	{
		command[i] = ft_strjoin(bin_path, argv[1]);
		i++;
	}
	while (i < argc - 1)
	{
		command[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	return (command);
}