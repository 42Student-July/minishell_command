#include "../includes/command.h"

void	new_sigint(int sig)
{
	printf("new_sigint\n");
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

int main(void)
{
	set_signal();
	printf("done set_signal\n");
	while (1)
		pause();
	return (0);
}