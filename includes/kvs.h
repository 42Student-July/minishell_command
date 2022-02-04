/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:27:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 14:45:10 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KVS_H
# define KVS_H

# define KEY 0
# define VALUE 1

typedef struct s_kvs
{
	char	*key;
	char	*value;
}	t_kvs;


void	free_all_kvs(t_kvs *kvs);
void	*create_content(char *key, char *value);

#endif