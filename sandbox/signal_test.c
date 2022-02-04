#include "../includes/command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_HISTORY_NO 10

void	new_sigint(int sig)
{
	printf("new_sigint\n");
	exit(EXIT_SUCCESS);
	// メインプログラムを呼び出す
}

void	set_sigint()
{
	struct sigaction act;
	act.sa_handler = new_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

void	new_sigquit(int sig)
{
	printf("new_sigquit\n");
	exit(EXIT_SUCCESS);
}

void	set_sigquit()
{
	struct sigaction act;
	act.sa_handler = new_sigquit;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signal()
{
	set_sigint();  // ctrl + c
	set_sigquit(); // ctrl + バックスラッシュ
}

void	test_readline()
{
	char *prompt = getenv("PS2");
	char *line = NULL;
	int history_i = 0;
	HIST_ENTRY *rm_history = NULL;

	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break ;
		printf("%s\n", line);
		add_history(line);
		if (++history_i > MAX_HISTORY_NO)
		{
			rm_history = remove_history(0);
			free(rm_history);
		}
		free(line);
	}
	printf("\n");
	clear_history();
}

/*
	実行前に環境変数PS2にプロンプト用の文字列を設定する
	例：export PS2='minishell $'
	コンパイルにはオプションとして-lreadlineを入れる
	実行中は上矢印キーで過去のコマンドが入力候補として表示される
	ctrl+d で終了
	MAX_HISTORY_NO より多くコマンドを入力すると古いコマンドから履歴が削除される
*/
int	main(void)
{
	set_signal();
	printf("done set_signal\n");
	test_readline();
	return (EXIT_SUCCESS);
}