/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:07:42 by tkirihar          #+#    #+#             */
/*   Updated: 2021/12/19 21:48:09 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 第3引数のバイト分第1引数に第2引数の文字列をコピーする関数 */
size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	if (len == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < len - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
