/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/10 17:42:02 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(char **strs)
{
	int	i;
	int	j;

	j = 0;
	while (strs[j])
	{
		i = 0;
		while (strs[j][i])
		{
			if (strs[j][i] < '0' && strs[j][i] > '9')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result *= sign);
}

int	ft_parsing(char **argv, t_table *table)
{
	if (ft_isdigit(argv))
	{
		ft_error("Error: Only digits are accepted.\n", table);
		return (1);
	}
	return (0);
}