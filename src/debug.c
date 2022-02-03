/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:31:50 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/03 13:33:30 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	print_command_debug(t_exec_attr *ea)
{
	size_t	i;

	i = 0;
	while (ea->command[i] != NULL)
	{
		printf("ea->command[i] : %s\n", ea->command[i]);
		i++;
	}
}
