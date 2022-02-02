/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 14:45:22 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	x_chdir(const char *path)
{
	if (chdir(path) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	my_cd(const char **command, char **environ)
{
	(void)environ;
	x_chdir(command[2]);
}

void	x_getcwd(char *pathname, int bufsiz)
{
	if (getcwd(pathname, bufsiz) == NULL)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	my_pwd(char **environ)
{
	char	pathname[BUFSIZ];

	(void)environ;
	x_getcwd(pathname, BUFSIZ);
	printf("%s\n", pathname);
}

// echo などの自作コマンドを実行する関数
bool	execute_self(const char **command, char **environ)
{
	(void)environ;
	if (ft_strncmp(command[1], CD, ft_strlen(CD)) == 0)
		my_cd(command, environ);
	else if (ft_strncmp(command[1], PWD, ft_strlen(PWD)) == 0)
		my_pwd(environ);
	else
		return (false);
	// my_pwd(environ);
	return (true);
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