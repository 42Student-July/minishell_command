/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:33 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/07 14:19:36 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	exec_self_exit(t_exec_attr *ea)
{
	(void)ea;
	exit(0);
}
