#include "../includes/command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	g_is_waiting_for_input;

void	interactive_sigint(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (!g_is_waiting_for_input)
		return ;
	printf("\n");
	rl_replace_line("", 0); // プロンプトのバッファをクリア
	rl_on_new_line();       // プロンプトを次の行に移動したいことを伝える？
	rl_redisplay();         // プロンプトを再描画
}

void	set_interactive_sigint()
{
	struct sigaction act;
	act.sa_sigaction = interactive_sigint;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

char	*x_readline()
{
	char *prompt;
	char *cmd;

	prompt = "minishell $";
	signal(SIGQUIT, SIG_IGN); // sigquitがきたら無視する
	set_interactive_sigint();
	g_is_waiting_for_input = true;
	cmd = readline(prompt);
	g_is_waiting_for_input = false;
	signal(SIGQUIT, SIG_DFL); // sigquitをデフォルト動作に戻す
	return (cmd);
}

void	test_readline()
{
	char *cmd = NULL;
	int history_i = 0;
	HIST_ENTRY *rm_history = NULL;

	while (1)
	{
		cmd = x_readline();
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
	clear_history();
}

/*
	コンパイル gcc -I /usr/local/opt/readline/include -lreadline -lhistory -L/usr/local/opt/readline/lib signal_test.c
	実行中は上矢印キーで過去のコマンドが入力候補として表示される
	ctrl+d で終了
	MAX_HISTORY_NO より多くコマンドを入力すると古いコマンドから履歴が削除される
*/
int	main(void)
{
	set_sigint();
	test_readline();
	return (EXIT_SUCCESS);
}