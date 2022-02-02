#include "../includes/command.h"

void	free_all(t_exec_attr *ea)
{
	int	i;

	i = 0;

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

void	abort_minishell(char *msg, t_exec_attr *ea)
{
	if (ea != NULL)
		free_all(ea);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
