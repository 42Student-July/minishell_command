/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 11:06:07 by tkirihar         ###   ########.fr       */
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

char *const	*create_command(int argc, const char *argv[])
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

bool	my_cd(char *const *command, char **environ)
{
	(void)environ;
	if (chdir(command[2]) == -1)
	{
		printf("Error");
	}
}

// echo などの自作コマンドを実行する関数
bool	execute_my_command(char *const *command, char **environ)
{
	(void)environ;
	printf("my command kita\n");
	if (ft_strncmp(command[1], CD, ft_strlen(CD)))
		my_cd(command, environ);
	return (true);
}

bool	is_my_command(const char *c)
{
	if (
		ft_strncmp(c, CD, ft_strlen(CD)) ||
		ft_strncmp(c, ECHO, ft_strlen(ECHO)) ||
		ft_strncmp(c, PWD, ft_strlen(PWD)) ||
		ft_strncmp(c, EXIT, ft_strlen(EXIT))
		)
		return (false);
	return (true);
}

void	hoge_fork(char *const *command, char **environ)
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
		execute_command(command, environ);
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

int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;
	int			command_num;

	environ = NULL;
	command_num = argc;
	// argvの引数は修正が必要そう
	if (is_my_command(argv[1]))
		execute_my_command(argv, environ);
	command = create_command(command_num, argv);
	hoge_fork(command, environ);
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	return (0);
}
