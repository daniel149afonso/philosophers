/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/28 22:39:48 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_number(char **strs)
{
	int	i;
	int	j;

	j = 1;
	while (strs[j])
	{
		i = 0;
		if (strs[j][i] == '\0')
			return (0);
		while (strs[j][i])
		{
			if (strs[j][i] < '0' || strs[j][i] > '9')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

long	ft_atol_v2(const char *str)
{
	int		i;
	long	result;
	int		length;

	i = 0;
	result = 0;
	length = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
		length++;
		if ((result > LONG_MAX) || length > 19)
			return (0);
	}
	return (result);
}

int	ft_parsing(char **argv, t_table *table)
{
	int	j;

	if (!is_number(argv))
	{
		ft_error("Error: Invalid number.\n", table);
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
			ft_error("Error: Number excceds LONG_MAX.\n",
				table);
			return (1);
		}
		j++;
	}
	return (0);
}
