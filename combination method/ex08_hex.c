	/* ************************************************************************** */
	/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex08_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:17:01 by kelevequ          #+#    #+#             */
/*   Updated: 2024/10/23 13:55:29 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(char *str);

void write_digit(int digit)
{
    char d = (digit < 10) ? (48 + digit) : (55 + digit);
    write(1, &d, 1);
}

void write_combn(int *x, int n)
{
    for (int i = 0; i < n; i++)
        write_digit(x[i]);
    write(1, "\n", 1);
}

int ft_check(int *x, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (x[j] == x[i] + (j - i) || x[j] == x[i] - (j - i))
                return 0;
        }
    }
    return 1;
}

void ft_compute(int n, int x_idx, int *x, int *used)
{
    if (x_idx == n)
    {
        write_combn(x, n);
        return;
    }
    
    for (int i = 1; i <= n; i++)
    {
        if (!used[i - 1])
        {
            x[x_idx] = i; // Place the current digit
            used[i - 1] = 1; // Mark as used

            if (ft_check(x, x_idx + 1)) // Check validity
                ft_compute(n, x_idx + 1, x, used); // Recur
            
            // No need to reset x[x_idx], just mark used as 0
            used[i - 1] = 0; // Backtrack
        }
    }
}

void ft_print_combn(int n)
{
    int *x = calloc(n, sizeof(int));
    int *used = calloc(n, sizeof(int)); // Track used digits
    ft_compute(n, 0, x, used);
    free(x);
    free(used);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 0;

    int n = ft_atoi(argv[1]);
    ft_print_combn(n);
    return 0;
}

