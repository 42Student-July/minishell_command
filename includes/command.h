/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:59:10 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 14:59:09 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "color.h"

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define MY_COMMAND_NUM 4
# define NAME 0


// execute_self.c
bool		is_self_cmd(const char *c);
bool		execute_self(const char **command, char **environ);

// execute_builtin.c
void		execute_builtin(char *const *command, char **environ);
char *const	*create_builtin_cmd(int argc, const char *argv[]);
void		x_execve(char *const *command, char *const *environ);
bool		is_not_exec_path(const char *command);

// self_pwd.c
void		self_pwd(char **environ);

// self_cd.c
void		self_cd(const char **command, char **environ);

#endif
