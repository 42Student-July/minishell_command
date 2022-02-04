/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:32:37 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 14:02:30 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}	t_lst;

typedef void(*	t_content_f)(void *);

int		ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
int		ft_lstaddone_front(t_lst **lst, t_lst *new);
void	ft_lstclear(t_lst **lst, void (*del)(void *));
int		ft_lstdel_front(t_lst **lst);
void	ft_lstdelone(t_lst *lst);
void	ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst	*ft_lstlast(t_lst *lst);
t_lst	*ft_lstmap(t_lst *lst, int (*f)(void *), void (*del)(void *));
t_lst	*ft_lstnew(void *c);
size_t	ft_lstsize(t_lst *lst);

#endif
