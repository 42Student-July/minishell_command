/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/08 11:06:56 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// 引数のコマンド名と実行時のコマンドが一致していたらtrue
bool	is_(const char *command, t_exec_attr *ea)
{
	if (ft_strncmp(ea->command[CMD_NAME], command, ft_strlen(command)) == 0)
		return (true);
	return (false);
}

bool	exec_in_main_process(t_exec_attr *ea)
{
	if (is_(CD, ea))
		exec_self_cd(ea);
	else if (is_(EXPORT, ea))
		exec_self_export(ea);
	else if (is_(EXIT, ea))
		exec_self_exit(ea);
	else if (is_(UNSET, ea))
		exec_self_unset(ea);
	else
		return (false);
	return (true);
}

void	exec_in_child_process(t_exec_attr *ea)
{
	if (is_(PWD, ea))
		exec_self_pwd(ea);
	else if (is_(ECHO, ea))
		exec_self_echo(ea);
	else if (is_(ENV, ea))
		exec_self_env(ea);
}

// echo などの自作コマンドを実行する関数
bool	execute_self(t_exec_attr *ea)
{
	pid_t	pid;

	// cdは子プロセスで実行しないので、forkする前に事前実行
	if (exec_in_main_process(ea))
		return (true);
	pid = fork();
	if (pid == -1)
		abort_minishell(FORK_ERROR, ea);
	else if (pid == 0)
	{
		if (is_redirect(ea))
			change_direction(ea);
		exec_in_child_process(ea);
	}
	return (true);
}

// TODO: いずれリファクタ
void	create_self_cmd_from_arg(int argc, const char **argv, t_exec_attr *ea)
{
	int		i;
	char	**command;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (command == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	while (i < argc - 1)
	{
		if (strcmp(argv[i + 1], "<") == 0)
		{
			ea->infile = strdup(argv[i + 2]);
			i++;
		}
		else if (ft_strncmp(argv[i + 1], ">", ft_strlen(argv[i + 1])) == 0)
		{
			ea->outfile = strdup(argv[i + 2]);
			i++;
		}
		else
		{
			command[i] = ft_strdup(argv[i + 1]);
			if (command[i] == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			i++;
		}
	}
	command[i] = NULL;
	ea->command = command;
}

// TODO: is_関数を使う
bool	is_self_cmd(const char *c)
{
	size_t	c_len;

	c_len = ft_strlen(c);
	if (ft_strncmp(c, CD, c_len) == 0)
		return (true);
	if (ft_strncmp(c, ECHO, c_len) == 0)
		return (true);
	if (ft_strncmp(c, PWD, c_len) == 0)
		return (true);
	if (ft_strncmp(c, EXIT, c_len) == 0)
		return (true);
	if (ft_strncmp(c, ENV, c_len) == 0)
		return (true);
	if (ft_strncmp(c, UNSET, c_len) == 0)
		return (true);
	return (false);
}
