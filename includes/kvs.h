/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:27:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/07 15:05:12 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KVS_H
# define KVS_H

# define KEY 0
# define VALUE 1
# define FIRST_INDEX 0

typedef struct s_kvs
{
	char	*key;
	char	*value;
}	t_kvs;


void	free_all_kvs(t_kvs *kvs);
void	*create_content_kvs(char *key, char *value);
char	*get_value(void *content);
char	*get_key(void *content);
t_lst	*get_min_key(t_lst *lst);
bool	is_lvalue_bigger_ascii(char *lvalue, char *rvalue);


#endif