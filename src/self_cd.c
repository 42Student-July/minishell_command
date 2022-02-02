/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/02 15:25:01 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

static void	x_chdir(const char *path)
{
	if (chdir(path) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	self_cd(char *const *command, char **environ)
{
	(void)environ;
	x_chdir(command[DIR]);
}
