/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:10:38 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/10 17:22:13 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free_table(t_table *table);

int	ft_error(char *msg, t_table *table)
{
	if (table)
		ft_free_table(table);
	printf("%s", msg);
	return (1);
}

void	ft_free_table(t_table *table)
{
	ft_destroy_mutex(table);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
}