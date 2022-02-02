/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 18:34:41 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// echo などの自作コマンドを実行する関数
bool	execute_self(int argc, const char *argv[], t_exec_attr *ea)
{
	create_self_cmd(argc, argv, ea);
	if (ft_strncmp(ea->command[CMD_NAME], CD, ft_strlen(CD)) == 0)
		self_cd(ea);
	else if (ft_strncmp(ea->command[CMD_NAME], PWD, ft_strlen(PWD)) == 0)
		self_pwd(ea);
	else
		return (false);
	return (true);
}

// TODO: いずれリファクタ
void	create_self_cmd(int argc, const char **argv, t_exec_attr *ea)
{
	int		i;
	char	**command;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (command == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	while (i < argc - 1)
	{
		if (strcmp(argv[i], "<") == 0)
		{
			ea->infile = strdup(argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], ">") == 0)
		{
			ea->outfile = strdup(argv[i + 1]);
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
	ea->command = command;
}

bool	is_self_cmd(const char *c)
{
	size_t	c_len;

	c_len = ft_strlen(c);
	if (
		ft_strncmp(c, CD, c_len)
		&& ft_strncmp(c, ECHO, c_len)
		&& ft_strncmp(c, PWD, c_len)
		&& ft_strncmp(c, EXIT, c_len)
	)
		return (false);
	return (true);
}