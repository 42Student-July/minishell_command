/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:59:10 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/04 20:35:30 by mhirabay         ###   ########.fr       */
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
# include "../lib/ft_lst/ft_lst.h"
# include "color.h"
# include "error_msg.h"
# include "kvs.h"

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define MY_COMMAND_NUM 4
# define CMD_NAME 0
# define CMD_ARG 1
# define DIR 1

typedef struct s_exec_attr
{
	char *const	*command;
	char		*infile;
	char		*outfile;
	t_lst		*env;
	t_lst		*export;
}	t_exec_attr;


// execute_self.c
bool		is_self_cmd(const char *c);
bool		execute_self(t_exec_attr *ea);
void		create_self_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea);
void		exec_in_child_process(t_exec_attr *ea);
void		exec_in_main_process(t_exec_attr *ea);


// execute_builtin.c
void		execute_builtin(t_exec_attr *ea);
void		create_builtin_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea);
void		x_execve(t_exec_attr *ea);
bool		is_not_exec_path(const char *command);

// self_pwd.c
void		exec_self_pwd(t_exec_attr *ea);

// self_cd.c
void		exec_self_cd(t_exec_attr *ea);

// self_env.c
void		exec_self_env(t_exec_attr *ea);

// self_export.c
void		exec_self_export(t_exec_attr *ea);

// error_handling.c
void		free_all(t_exec_attr *ea);
void		abort_minishell(char *msg, t_exec_attr *ea);

// redirect_process.c
void		change_direction(t_exec_attr *ea);
bool		is_redirect(t_exec_attr *ea);

// debug.c
void		print_command_debug(t_exec_attr *ea);
void		print_kvs_debug(void *content);

// env.c
void		store_env(t_exec_attr *ea, char **environ);
void		free_line(char **line);
void		print_env(void *content);

#endif
