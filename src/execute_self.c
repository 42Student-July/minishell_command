/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 17:13:14 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// echo などの自作コマンドを実行する関数
bool	execute_self(char *const *command, char **environ)
{
	(void)environ;
	if (ft_strncmp(command[CMD_NAME], CD, ft_strlen(CD)) == 0)
		self_cd(command, environ);
	else if (ft_strncmp(command[CMD_NAME], PWD, ft_strlen(PWD)) == 0)
		self_pwd(environ);
	else
		return (false);
	// my_pwd(environ);
	return (true);
}

// TODO: いずれリファクタ
char *const *create_self_cmd(int argc, const char **argv)
{
	int		i;
	char 	**command;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (command == NULL)
		 abort_minishell(MALLOC_ERROR, command);
	while (i < argc - 1)
	{
		command[i] = ft_strdup(argv[i + 1]);
		if (command[i] == NULL)
			abort_minishell(MALLOC_ERROR, command);
		i++;
	}
	return (command);
}

bool	is_self_cmd(const char *c)
{
	size_t c_len;

	c_len = ft_strlen(c);
	if (
		ft_strncmp(c, CD, c_len) &&
		ft_strncmp(c, ECHO, c_len) &&
		ft_strncmp(c, PWD, c_len) &&
		ft_strncmp(c, EXIT, c_len)
		)
		return (false);
	return (true);
}