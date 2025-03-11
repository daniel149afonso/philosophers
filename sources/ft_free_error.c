/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:10:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/11 18:02:06 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free_table(t_table *table);

int	ft_error(char *msg, t_table *table)
{
	ft_free_table(table);
	printf("%s", msg);
	return (1);
}

void	ft_free_table(t_table *table)
{
	if (table)
	{
		ft_destroy_mutex(table);
		if (table->philos)
			free(table->philos);
		if (table->forks)
			free(table->forks);
		free(table);
	}
}