/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:59:10 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/02 17:42:23 by tkirihar         ###   ########.fr       */
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
# include "error_msg.h"

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define MY_COMMAND_NUM 4
# define CMD_NAME 0
# define DIR 1

typedef struct s_exec_attr
{
	char *const *command;
	char 		*infile;
	char		*outfile;
	char		**env;
}	t_exec_attr;


// execute_self.c
bool		is_self_cmd(const char *c);
bool		execute_self(int argc, const char *argv[], char **environ);
char *const *create_self_cmd(int argc, const char **argv, char *infile, char *outfile);

// execute_builtin.c
void		execute_builtin(char *const *command, char **environ);
char *const	*create_builtin_cmd(int argc, const char *argv[]);
void		x_execve(char *const *command, char *const *environ);
bool		is_not_exec_path(const char *command);

// self_pwd.c
void		self_pwd(char **environ);

// self_cd.c
void		self_cd(char *const *command, char **environ);

// error_handling.c
void	free_all(char **command);
void	abort_minishell(char *msg, char **command);

#endif
