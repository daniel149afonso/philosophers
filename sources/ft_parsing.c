/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/10 21:34:03 by daafonso         ###   ########.fr       */
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

long	ft_atol_v2(const char *str, t_table *table)
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
		{
			ft_error("Error: Number excceds LONG_MAX\n", table);
			return (0);
		}
	}
	return (result *= sign);
}

int	ft_parsing(char **argv, t_table *table)
{
	if (ft_is_positive_num(argv) == -1)
	{
		ft_error("Error: Only digits are accepted.\n", table);
		return (1);
	}
	return (0);
}