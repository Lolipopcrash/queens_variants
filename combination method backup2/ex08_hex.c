	/* ************************************************************************** */
	/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex08_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:17:01 by kelevequ          #+#    #+#             */
/*   Updated: 2024/10/23 13:45:37 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_atoi(char *str);

void	write_digit(int digit)
{
	char	d;
	
	if (digit < 10)
	{
		d = 48 + digit;
	}
	else if (digit >= 10)
	{
		d = 55 + digit;
	}
	write(1, &d, 1);
}

void	write_combn(int *x, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write_digit(x[i] - 1);
		i++;
	}
	write(1, "\n", 1);
}

int		ft_check(int *x, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (x[j] == x[i] + (j - i) || x[j] == x[i] - (j - i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_validcomb(int *x, int x_idx, int i, int n, int *used)
{
	if (used[i - 1])
		return (0);
	used[i - 1] = 1;
	x[x_idx] = i;
	if (x_idx == n - 1)
		if (!ft_check(x, n))
		{
			used[i - 1] = 0;
			return (0);
		}
	return (1);
}

int		ft_compute(int n, int x_idx, int *x, int *used)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (x_idx == n)
	{
		write_combn(x, n);
		return (1);
	}
	while (i <= n)
	{
		if (ft_validcomb(x, x_idx, i, n, used))
		{
			x[x_idx] = i;
			count += ft_compute(n, x_idx + 1, x, used);
			used[i - 1] = 0;
		}
		i++;
	}
	return (count);
}

void	ft_print_combn(int n)
{
	int	*x;
	int	*used;

	x = calloc(n, sizeof(int));
	used = calloc(n, sizeof(int));
	printf("\nTotal Solutions found: %d\n", ft_compute(n, 0, x, used));
	free(x);
	free(used);
}

int	main(int argc, char *argv[])
{
	int	n;

	if (argc != 2)
		return (0);
	n = ft_atoi(argv[1]);
	ft_print_combn(n);
	return (0);
}
