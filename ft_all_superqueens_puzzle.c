/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:58:11 by kelevequ          #+#    #+#             */
/*   Updated: 2024/09/26 16:47:09 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef	struct s_checks
{
	bool	super;
	bool	funda;
	int		*cols;
	int		*diags1;
	int		*diags2;
	int		*knights;
	int		size;
}	t_checks;

void	ft_putnbr(int nb)
{
	char	ch_nb;

	if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else if (nb < 0)
	{
		nb = 0 - nb;
		write(1, "-", 1);
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	if (nb != -2147483648)
	{
		ch_nb = 48 + (nb % 10);
		write(1, &ch_nb, 1);
	}
}

void	ft_print(int *solve, int size)
{
	char	c;
	int		i;

	i = 0;
	while (i < size * size)
	{
		if (solve[i] != 0)
		{
			if (i % size < 10)
				c = 48 + (i % size);
			else
				c = 65 + ((i % size) - 10);
			write(1, &c, 1);
		}
		i++;
	}
	write(1, "\n", 1);
}
/*
void	ft_print_grid(int *solve)
{
	int	i;
	char	c;

	i = 0;
	while (i < 100)
	{
		c = 48 + solve[i];
		if((i + 1) % 10 == 0)
		{
			write(1, &c, 1);
			write(1, "\n", 1);
		}
		else
		{
			write(1, &c, 1);
			write(1, " ", 1);
		}
		i++;
	}
}
*/
int	ft_valid(int row, int col, t_checks *checks)
{
	if (checks->cols[col] || 
		checks->diags1[row - col + checks->size] || 
		checks->diags2[row + col] || 
		checks->knights[row * checks->size + col])
		return (0);
	return (1);
}

void	ft_place_checks(int row, int col, t_checks *checks)
{
	int	knight_moves[8][2] = {
		{-2, -1}, {-2, +1}, {-1, -2}, {-1, +2},
		{+1, -2}, {+1, +2}, {+2, -1}, {+2, +1}
	};
	int	temprow;
	int	tempcol;
	int	i;

	checks->cols[col] = 1;
	checks->diags1[row - col + checks->size] = 1;
	checks->diags2[row + col] = 1;
	if (checks->super)
	{
		i = 0;
		while (i < 8)
		{
			temprow = row + knight_moves[i][0];
			tempcol = col + knight_moves[i][1];
			if (0 <= temprow && temprow < checks->size && 0 <= tempcol && tempcol < checks->size)
				checks->knights[temprow * checks->size + tempcol]++;
			i++;
		}
	}
}

void	ft_remov_checks(int row, int col, t_checks *checks)
{
	int	knight_moves[8][2] = {
		{-2, -1}, {-2, +1}, {-1, -2}, {-1, +2},
		{+1, -2}, {+1, +2}, {+2, -1}, {+2, +1}
	};
	int	temprow;
	int	tempcol;
	int	i;

	checks->cols[col] = 0;
	checks->diags1[row - col + checks->size] = 0;
	checks->diags2[row + col] = 0;
	if (checks->super)
	{
		i = 0;
		while (i < 8)
		{
			temprow = row + knight_moves[i][0];
			tempcol = col + knight_moves[i][1];
			if (0 <= temprow && temprow < checks->size && 0 <= tempcol && tempcol < checks->size)
				checks->knights[temprow * checks->size + tempcol]--;
			i++;
		}
	}
}

int	ft_solve(int *solve, int row, t_checks *checks, int j)
{
	int	col;
	int	count;

	count = 0;
	if (row == checks->size && ft_is_fundamental(solve))
	{
		ft_print(solve, checks->size);
		return (1);
	}
	col = 0;
	while (col < checks->size)
	{
		if (ft_valid(row, col, checks))
		{
			solve[row * checks->size + col] = row + 1;
			ft_place_checks(row, col, checks);
			count += ft_solve(solve, row + 1, checks, j);
			solve[row * checks->size + col] = 0;
			ft_remov_checks(row, col, checks);
		}
		col++;
	}
	return (count);
}

int	ft_initialize(int *tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		tab[i] = 0;
		i++;
	}
	return (*tab);
}

void	free_checks(t_checks *checks)
{
	if (checks)
	{
		free(checks->cols);
		free(checks->diags1);
		free(checks->diags2);
		free(checks->knights);
		free(checks);
	}
}

t_checks	*ft_alloc(int size)
{
	t_checks *checks = malloc(sizeof(t_checks));
	checks->size = size;
	checks->cols = malloc(size * sizeof(int));
	checks->diags1 = malloc(2 * size * sizeof(int));
	checks->diags2 = malloc(2 * size * sizeof(int));
	checks->knights = malloc(size * size * sizeof(int));

	if (!checks->cols || !checks->diags1 || !checks->diags2 || !checks->knights)
	{
		free_checks(checks);
		return (NULL);
	}

	ft_initialize(checks->cols, size);
	ft_initialize(checks->diags1, size * 2);
	ft_initialize(checks->diags2, size * 2);
	ft_initialize(checks->knights, size * size);

	return (checks);
}

int	ft_n_queens_puzzle(int size, bool super, bool funda)
{
	int	count;
	int *solve;
	t_checks *checks;

	solve = malloc(size * size * sizeof(int));
	ft_initialize(solve, size * size);
	checks = ft_alloc(size);
	if (!checks)
	{
		free(solve);
		return (-1);
	}

	checks->super = super;
	checks->funda = funda;

	count = ft_solve(solve, 0, checks, 0);
	free(solve);
	free_checks(checks);
	return (count);
}

int	ft_atoi(char *str)
{
	int result = 0;
	int sign = 0;
	int i = 0;

	while (str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign++;
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (sign % 2 == 1)
		result = -result;
	return (result);
}

void	ft_input_option(int size, bool super, bool funda)
{
	if (super && !funda)
		printf("%d Superqueens Puzzle ", size);
	else if (super && funda)
		printf("%d Superqueens Puzzle Fundamental ", size);
	else if (!super && funda)
		printf("%d Queens Puzzle Fundamental ", size);
	else
		printf("%d Queens Puzzle ", size);
}

int	main(int argc, char *argv[])
{
	bool	super;
	bool	funda;
	int		size;
	int		n_solutions;

	if (argc < 2)
	{
		printf("Input format is: ./executable \'(size)\' \'(0 or 1 for superqueens)\' \'(0 or 1 for fundamentals)\'\n");
		return (0);
	}
	
	size = ft_atoi(argv[1]);
	if (argv[2][0] != '\0')
		super = ft_atoi(argv[2]);
	else
		super = 0;

	if (argv[3][0] != '\0')
		funda = ft_atoi(argv[2]);
	else
		funda = 0;

	printf("Finding size %d solutions:\n", size);
		n_solutions = ft_n_queens_puzzle(size, super, funda);
	printf("Number of ");
	ft_input_option(size, super, funda);
	printf("Solutions found: %d\n", n_solutions);
	return (0);
}