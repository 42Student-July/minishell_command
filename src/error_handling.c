#include "../includes/command.h"

void	free_all(char **command)
{
	int	i;

	i = 0;
	if (command != NULL)
	{
		while (command[i] != NULL)
		{
			free(command[i]);
			i++;
		}
		free(command);
	}
}

void	abort_minishell(char *msg, char **command)
{
	if (command != NULL)
		free_all(command);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
