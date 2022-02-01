/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:06:33 by tkirihar          #+#    #+#             */
/*   Updated: 2021/12/19 22:51:53 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 第3引数のバイト分第1引数の先頭から第2引数の文字を探す関数 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	size_t			len;

	char_s = (unsigned char *)s;
	len = 0;
	while (len < n)
	{
		if (char_s[len] == c)
			return ((void *)s + len);
		else
			len++;
	}
	return (NULL);
}
