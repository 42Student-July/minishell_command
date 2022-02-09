/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/09 10:59:51 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	execute_builtin(t_exec_attr *ea)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		abort_minishell(FORK_ERROR, ea);
	else if (pid == 0)
	{
		if (is_redirect(ea))
			change_direction(ea);
		x_execve(ea);
		exit(0);
	}
	else
	{
		pid = wait(&status);
		if (pid == -1)
			abort_minishell(FORK_ERROR, ea);
	}
}

void	x_execve(t_exec_attr *ea)
{
	char	**environ;

	environ = convert_envlst_to_array(ea);
	if (execve(ea->command[CMD_NAME], ea->command, environ) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		free(environ);
		exit(EXIT_FAILURE);
	}
	free(environ);
}

bool	is_not_exec_path(const char *command)
{
	size_t	i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (false);
		i++;
	}
	return (true);
}

void	create_builtin_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea)
{
	int			i;
	char		*bin_path;
	char		**command;
	char		*arg;

	i = 0;
	bin_path = "/bin/";
	// argv[0]は実行コマンドなんで、なくす。
	// 最後のNULL止めのために+1する。
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (command == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	if (is_not_exec_path(argv[1]))
	{
		command[i] = ft_strjoin(bin_path, argv[1]);
		if (command[i] == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		i++;
	}
	while (i < argc - 1)
	{
		// TODO: この辺わかりにくいので、リファクタ検討
		// parseの方で判定できたらそれがよい。
		if (strcmp(argv[i + 1], "<") == 0)
		{
			ea->infile = strdup(argv[i + 2]);
			i++;
		}
		else if (ft_strncmp(argv[i + 1], ">", ft_strlen(argv[i + 1])) == 0)
		{
			ea->outfile = strdup(argv[i + 2]);
			i++;
		}
		else
		{
			arg = (char *)argv[i + 1];
			if (is_dollar(arg))
			{
				arg = convert_env_var(ea, arg);
				if (arg == NULL)
				{
					// $の後、環境変数に指定していない値が来た時、その引数の読み込みを飛ばす
					// 検証をちゃんとしていないので、この辺は要検討
					i++;
					continue;
				}
			}
			command[i] = ft_strdup(arg);
			if (command[i] == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			i++;
		}
	}
	command[i] = NULL;
	ea->command = command;
}

char	**convert_envlst_to_array(t_exec_attr *ea)
{
	char	**array;
	size_t	env_lst_size;
	size_t	i;
	t_lst	*tmp;

	i = 0;
	tmp = ea->env;
	env_lst_size = ft_lstsize(tmp);
	array = (char **)malloc(sizeof(char *) * (env_lst_size + NULL_CHAR));
	if (array == NULL)
		return (NULL);
	while (i < env_lst_size)
	{
		//　TODO: 行数長くなっちゃうからget_keyの引数はlstでもいいのかも
		array[i] = create_environ_line(\
			get_key(tmp->content), get_value(tmp->content), false);
		if (array[i] == NULL)
			abort_minishell_with(MALLOC_ERROR, ea, array);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	// print_array(array);
	return (array);
}


char	*create_environ_line(char *key, char *value, bool is_end)
{
	size_t	key_size;
	size_t	value_size;
	size_t	line_size;
	char	*line;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	line_size = key_size + EQUAL + value_size + LF;
	line = (char *)malloc(sizeof(char) * line_size);
	if (line == NULL)
		return (NULL);
	ft_strlcat(line, key, line_size);
	ft_strlcat(line, "=", line_size);
	ft_strlcat(line, value, line_size);
	if (is_end)
		ft_strlcat(line, "\n", line_size);
	else
		ft_strlcat(line, "\0", line_size);
	return (line);
}
