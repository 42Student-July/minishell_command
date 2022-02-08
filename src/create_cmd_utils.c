/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:40:07 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/08 17:48:01 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

bool	is_dollar(char *arg)
{
	// TODO:あとでけす
	// readlineが無いので、引数に$を入れると元々の方の環境変数が呼ばれる。
	// quoteをつけても読めるように対応する
	// arg++;
	if (*arg == '$')
		return (true);
	return (false);
}

char	*convert_env_var(t_exec_attr *ea, char *arg)
{
	char	*key;
	t_lst	*ret;
	char	*value;

	// $はkeyに不要なので一つポインタを進める
	// TODO:あとで消す quote対応
	arg = ft_strtrim(arg, "\'");
	key = ++arg;
	ret = get_lst_by_key(ea->env, key);
	if (ret == NULL)
		return (NULL);
	value = get_value(ret->content);
	return (value);
}
