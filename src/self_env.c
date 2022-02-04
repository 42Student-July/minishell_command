/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:36:05 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 16:44:47 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// TODO:引数あるバージョンは未対応
void	exec_self_env(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_env;
	ft_lstiter(ea->env, f);
}
