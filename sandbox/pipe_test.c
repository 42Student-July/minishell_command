#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <../lib/libft/libft.h>

static int	get_pipe_cnt(char **command_lst)
{
	int	i;
	int	pipe_cnt;

	i = 0;
	pipe_cnt = 0;
	while (command_lst[i] != NULL)
	{
		if (ft_strncmp(command_lst[i], '|', 1) == 0)
			pipe_cnt++;
		i++;
	}
	return (pipe_cnt);
}

static void	read_command_lst(char **command_lst, int *pipe_locate)
{
	int	i;
	int	pipe_cnt;


	i = 0;
	pipe_cnt = 0;
	while (command_lst[i] != NULL)
	{
		if (ft_strncmp(command_lst[i], '|', 1) == 0)
		{
			pipe_cnt++;
			pipe_locate[pipe_cnt] = i;
			command_lst[i] = NULL;
		}
		i++;
	}
}

void	init_pfd(int **pfd)
{
	pfd = ;
}

int main()
{
	char *command_lst[] = {"ls", NULL};
	int i;
	int	*pipe_locate;
	int	pipe_cnt;
	int	**pfd;

	pipe_cnt = get_pipe_cnt(command_lst);
	if (pipe_cnt == 0)
	{
		// パイプがないケース
		// ここに今までの処理を書く
	}
	else
	{
		// パイプがあるケース
		pipe_locate = (int *)malloc(sizeof(int) * pipe_cnt + 1);
		pipe_locate[0] = -1;
		read_command_lst(command_lst, pipe_locate);
		init_pfd(pfd);
		pfd = (int *)malloc(sizeof(int) * pipe_cnt);
		while ()
		{
			/* code */
		}


	}
	// for (i = 0; argv[i] != NULL; i++)
	// {
	// 	if (strcmp(argv[i], "|") == 0)
	// 	{
	// 		pipe_cnt++;
	// 		pipe_locate[pipe_cnt] = i;
	// 		argv[i] = NULL;
	// 	}
	// }
	// int pfd[9][2];

	for (i = 0; i < pipe_cnt + 1 && pipe_cnt != 0; i++)
	{
		if (i != pipe_cnt)
		{
			pipe(pfd[i]);  //最後のコマンドでなければパイプを作成
		}
		if (fork() == 0)
		{
			//子プロセス
			if (i == 0)
			{
				//最初のコマンドなので、標準出力をパイプの入り口へつなげる
				dup2(pfd[i][1], 1);
				close(pfd[i][0]); close(pfd[i][1]);
			}
			else if (i == pipe_cnt)
			{
				//最後のコマンドなので、標準入力をパイプの出口へつなげる
				dup2(pfd[i - 1][0], 0);
				close(pfd[i - 1][0]); close(pfd[i - 1][1]);
			}
			else
			{
				//途中のコマンドなので、上記の処理を両方やる
				dup2(pfd[i - 1][0], 0);
				dup2(pfd[i][1], 1);
				close(pfd[i - 1][0]); close(pfd[i - 1][1]);
				close(pfd[i][0]); close(pfd[i][1]);
			}
			execvp(argv[pipe_locate[i] + 1], argv + pipe_locate[i] + 1);
			exit(0);
		}
		else if (i > 0)
		{
			//親プロセス
			//つなげ終わったパイプは閉じる
			close(pfd[i - 1][0]); close(pfd[i - 1][1]);
		}
	}
	int status;

	for (i = 0; i < pipe_cnt + 1; i++) {
		wait(&status);
	}
	return 0;
}