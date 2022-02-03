/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/03 09:35:55 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	execute_builtin(t_exec_attr *ea)
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
		change_direction(ea);
		x_execve(ea);
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

void	x_execve(t_exec_attr *ea)
{
	// TODO: NULL判定などは未実装
	if (execve(ea->command[CMD_NAME], ea->command, ea->env) == -1)
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

void	create_builtin_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea)
{
	int		i;
	char	*bin_path;
	char	**command;

	i = 0;
	bin_path = "/bin/";
	// argv[0]は実行コマンドなんで、なくす。
	// 最後のNULL止めのために+1する。
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (command == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	if (is_not_exec_path(argv[1]))
	{
		command[i] = ft_strjoin(bin_path, argv[1]);
		if (command[i] == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		i++;
	}
	while (i < argc - 1)
	{
		command[i] = ft_strdup(argv[i + 1]);
		if (command[i] == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		i++;
	}
	ea->command = command;
}