#include <unistd.h>

void	ft_print_grid(char *str)
{
	char	c;
	int	i;

	i = 0;
	while (i < 100)
	{
		c = 48 + (i % 10);
		if (str[i / 10] == c)
			write(1, &c, 1);
		else
			write(1, ".", 1);
		if (i % 10 == 9)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	ft_print_grid(argv[1]);
	return (0);
}
