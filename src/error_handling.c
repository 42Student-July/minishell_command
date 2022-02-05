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
	//TODO: いずれ削除する
	printf("msg : %s\n", msg);
	perror(msg);
	if (ea != NULL)
		free_all(ea);
	exit(EXIT_FAILURE);
}
