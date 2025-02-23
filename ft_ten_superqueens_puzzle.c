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

#include <unistd.h>

typedef	struct s_checks
{
	int	cols[10];
	int	diags1[20];
	int	diags2[20];
	int	knights[100];
}	t_checks;

void	ft_print(int *solve)
{
	char	c;
	int		i;

	i = 0;
	while (i < 100)
	{
		if (solve[i] != 0)
		{
			c = 48 + (i % 10);
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
		checks->diags1[row - col + 10] || 
		checks->diags2[row + col] || 
		checks->knights[row * 10 + col])
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
	checks->diags1[row - col + 10] = 1;
	checks->diags2[row + col] = 1;
	i = 0;
	while (i < 8)
	{
		temprow = row + knight_moves[i][0];
		tempcol = col + knight_moves[i][1];
		if (0 <= temprow && temprow < 10 && 0 <= tempcol && tempcol < 10)
			checks->knights[temprow * 10 + tempcol]++;
		i++;
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
	checks->diags1[row - col + 10] = 0;
	checks->diags2[row + col] = 0;
	i = 0;
	while (i < 8)
	{
		temprow = row + knight_moves[i][0];
		tempcol = col + knight_moves[i][1];
		if (0 <= temprow && temprow < 10 && 0 <= tempcol && tempcol < 10)
			checks->knights[temprow * 10 + tempcol]--;
		i++;
	}
}

int	ft_solve(int *solve, int row, t_checks *checks)
{
	int	col;
	int	count;

	count = 0;
	if (row == 10)
	{
		ft_print(solve);
		return (1);
	}
	col = 0;
	while (col < 10)
	{
		if (ft_valid(row, col, checks))
		{
			solve[row * 10 + col] = row + 1;
			ft_place_checks(row, col, checks);
			count += ft_solve(solve, row + 1, checks);
			solve[row * 10 + col] = 0;
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

int	ft_ten_queens_puzzle(void)
{
	t_checks	checks;
	int	solve[100];

	ft_initialize(solve, 100);
	ft_initialize(checks.cols, 10);
	ft_initialize(checks.diags1, 20);
	ft_initialize(checks.diags2, 20);
	ft_initialize(checks.knights, 100);
	return (ft_solve(solve, 0, &checks));
}

#include <stdio.h>

int	main(void)
{
	printf("Count: %d\n", ft_ten_queens_puzzle());
	return (0);
}
