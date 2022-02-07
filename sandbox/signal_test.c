#include "../includes/command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	g_is_waiting_for_input;

void	new_sigint(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (!g_is_waiting_for_input)
		return ;
	printf("\n");
	rl_replace_line("", 0); // プロンプトのバッファをクリア
	rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	rl_redisplay();         // プロンプトを再描画
}

void	set_sigint()
{
	struct sigaction act;
	act.sa_sigaction = new_sigint;
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
	// set_sigquit(); // ctrl + バックスラッシュ
}

void	test_readline()
{
	char *prompt = "minishell $";
	char *cmd = NULL;
	int history_i = 0;
	HIST_ENTRY *rm_history = NULL;

	while (1)
	{
		g_is_waiting_for_input = true;
		cmd = readline(prompt);
		g_is_waiting_for_input = false;
		if (cmd == NULL)
			break ;
		printf("%s\n", cmd);
		if (strlen(cmd) > 0) // 空文字列をヒストリーに入れないための対処法
			add_history(cmd);
		printf("start\n");
		sleep(3);
		printf("end\n");
		free(cmd);
	}
	printf("\n");
	clear_history();
}

/*
	コンパイルにはオプションとして-lreadlineを入れる
	実行中は上矢印キーで過去のコマンドが入力候補として表示される
	ctrl+d で終了
	MAX_HISTORY_NO より多くコマンドを入力すると古いコマンドから履歴が削除される
*/
int	main(void)
{
	set_signal();
	test_readline();
	return (EXIT_SUCCESS);
}