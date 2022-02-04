#include "../includes/command.h"



int main(void)
{
	set_signal();
	printf("done set_signal\n");
	while (1)
		pause();
	return (0);
}