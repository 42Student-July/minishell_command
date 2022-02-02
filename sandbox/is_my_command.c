#include "../includes/command.h"

bool	is_my_command(const char *c)
{
	if (ft_strncmp(c, CD, ft_strlen(CD)))
		return (true);
	if (ft_strncmp(c, ECHO, ft_strlen(ECHO)))
		return (true);
	if (ft_strncmp(c, PWD, ft_strlen(PWD)))
		return (true);
	if (ft_strncmp(c, EXIT, ft_strlen(EXIT)))
		return (true);
	return (false);
}

int	main(int argc, const char *argv[])
{
	(void)argc;
	printf(" ft_strncmp(c, ECHO, ft_strlen(ECHO)) = %d\n", ft_strncmp(argv[1], ECHO, ft_strlen(ECHO)));
	if (is_my_command(argv[1]))
	{
		printf("true\n");
	}
	else
		printf("false\n");
	return (0);
}