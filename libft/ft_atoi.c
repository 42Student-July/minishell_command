/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:06:06 by tkirihar          #+#    #+#             */
/*   Updated: 2021/12/19 23:07:45 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	process_flow(int sign)
{
	if (sign == -1)
	{
		return (LONG_MIN);
	}
	return (LONG_MAX);
}

/* 引数の数字を数値に変換する関数 */
int	ft_atoi(const char *str)
{
	size_t		i;
	long		num;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((num * 10 + (str[i] - '0')) / 10 != num)
			return ((int)process_flow(sign));
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}
