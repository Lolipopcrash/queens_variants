/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelevequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:33:30 by kelevequ          #+#    #+#             */
/*   Updated: 2024/09/18 19:54:07 by kelevequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_negflag(char *str, int i, int *neg)
{
	if (str[i] == '-')
		(*neg)++;
	return (*neg);
}

int	ft_valid(char *str, int i, int *n_flag, int *s_flag)
{
	if ((str[i] == 45 || str[i] == 43) && *n_flag != 1)
	{
		*s_flag = 1;
		return (1);
	}
	else if (48 <= str[i] && str[i] <= 57)
	{
		*n_flag = 1;
		return (1);
	}
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	n_flag;
	int	s_flag;
	int	result;

	i = 0;
	neg = 0;
	n_flag = 0;
	s_flag = 0;
	result = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i] != '\0' && ft_valid(str, i, &n_flag, &s_flag))
	{
		if (s_flag == 1 && n_flag == 0)
			ft_negflag(str, i, &neg);
		else if (48 <= str[i] && str[i] <= 57)
			result = result * 10 + (str[i] - 48);
		i++;
	}
	if ((neg % 2) == 1)
		result = 0 - result;
	return (result);
}
/*
#include <stdio.h>

int main() 
{
    printf("Input: '  -1234'\n");
    printf("Result: %d\n", ft_atoi("  -1234"));  // Expected output: -1234
    printf("Input: '42'\n");
    printf("Result: %d\n", ft_atoi("42"));       // Expected output: 42
    printf("Input: '  +567'\n");
    printf("Result: %d\n", ft_atoi("  +567"));   // Expected output: 567
    printf("Input: '42abc'\n");
    printf("Result: %d\n", ft_atoi("42abc"));    // Expected output: 42
    printf("Input: '  ----1234'\n");
    printf("Result: %d\n", ft_atoi("  ----1234"));  // Expected output: 1234
    printf("Input: '+--+-42'\n");
    printf("Result: %d\n", ft_atoi("+--+-42"));       // Expected output: -42
    printf("Input: ' + +567-'\n");
    printf("Result: %d\n", ft_atoi(" + +567-"));   // Expected output: ''
    printf("Input: '42+abc'\n");
    printf("Result: %d\n", ft_atoi("42+abc"));    // Expected output: 42
    printf("Input: '0042+abc'\n");
    printf("Result: %d\n", ft_atoi("0042+abc"));    // Expected output: 42

    return 0;
}*/
