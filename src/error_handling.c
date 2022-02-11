#include "../includes/command.h"

void	free_exec_attr(t_exec_attr *ea)
{
	int	i;

	i = 0;
		// envlistとexportlistをfreeする
	t_lst *tmp_env;
	tmp_env = ea->env_lst;
	while (ea->env_lst != NULL)
	{
		free_all_kvs((t_kvs *)ea->env_lst->content);
		// if (get_key(ea->env_lst) != NULL)
		// 	free(get_key(ea->env_lst));
		// if (get_value(ea->env_lst) != NULL)
		// 	free(get_value(ea->env_lst));
		// free(ea->env_lst->content);
		// free(ea->env_lst);
		ea->env_lst = ea->env_lst->next;
	}
	t_lst *tmp_export;
	tmp_export = ea->export_lst;
	while (ea->export_lst != NULL)
	{
		free_all_kvs((t_kvs *)ea->export_lst->content);
		ea->export_lst = ea->export_lst->next;
	}
	while (tmp_env != NULL)
	{
		free(tmp_env);
		tmp_env = tmp_env->next;
	}
	while (tmp_export != NULL)
	{
		free(tmp_export);
		tmp_export = tmp_export->next;
	}

	if (ea->command != NULL)
	{
		while (ea->command[i] != NULL)
		{
			free(ea->command[i]);
			i++;
		}
		free((void *)ea->command);
	}
	if (ea != NULL)
		free(ea);
}

void	free_char_dptr(char **dptr)
{
	size_t	i;

	i = 0;
	if (dptr != NULL)
	{
		while (dptr[i] != NULL)
		{
			free(dptr[i]);
			i++;
		}
		free(dptr);
	}
}

void	abort_minishell(char *msg, t_exec_attr *ea)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}

void	abort_minishell_with(char *msg, t_exec_attr *ea, char **split)
{
	if (split != NULL)
		free_char_dptr(split);
	perror(msg);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}

