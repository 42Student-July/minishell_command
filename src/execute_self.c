/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 14:56:14 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// echo などの自作コマンドを実行する関数
bool	execute_self(const char **command, char **environ)
{
	(void)environ;
	if (ft_strncmp(command[1], CD, ft_strlen(CD)) == 0)
		self_cd(command, environ);
	else if (ft_strncmp(command[1], PWD, ft_strlen(PWD)) == 0)
		self_pwd(environ);
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