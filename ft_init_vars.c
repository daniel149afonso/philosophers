/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:16 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/04 03:44:37 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_table(t_table *table, char *argv, int argc)
{
	(void)argc;
	table->nb_philo = argv[1];
	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->forks)
		return (ft_error("Error: Failed to allocate forks\n"));
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (ft_error("Error: Failed to allocate philos\n"));
	return (0);
}