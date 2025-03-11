/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/11 16:54:19 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_positive_num(char **strs)
{
	int	i;
	int	j;

	j = 1;
	while (strs[j])
	{
		i = 0;
		if (strs[j][i] == '+')
			i++;
		while (strs[j][i])
		{
			if (strs[j][i] < '0' || strs[j][i] > '9')
				return (-1);
			i++;
		}
		j++;
	}
	return (0);
}

long	ft_atol_v2(const char *str)
{
	int		i;
	int		sign;
	long	result;
	int		length;

	i = 0;
	sign = 1;
	result = 0;
	length = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
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
		length++;
		if ((result > LONG_MAX) || length > 19)
			return (0);
	}
	return (result *= sign);
}

int	ft_parsing(char **argv, t_table *table)
{
	int	j;

	if (ft_is_positive_num(argv) == -1)
	{
		ft_error("Error: Only positive numbers are allowed"
			" (without duplicated sign).\n", table);
		return (1);
	}
	if (ft_atol_v2(argv[1]) > MAX_PHILOS)
	{
		ft_error("Error: Maximum 200 philosophers can be added.\n", table);
		return (1);
	}
	j = 1;
	while (argv[j])
	{
		if (!ft_atol_v2(argv[j]))
		{
			ft_error("Error: Non valid number or number excceds LONG_MAX\n",
				table);
			return (1);
		}
		j++;
	}
	return (0);
}
