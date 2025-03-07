/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:54:12 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/05 15:39:06 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_alloc_struct_in_table(t_table **table, long nb_philo)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
		return (ft_error("Error: Failed to allocate table\n"));
	memset(*table, 0, sizeof(t_table));
	(*table)->forks = malloc(sizeof(t_fork) * nb_philo);
	if (!(*table)->forks)
		return (ft_error("Error: Failed to allocate forks\n"));
	(*table)->philos = malloc(sizeof(t_philo) * nb_philo);
	if (!(*table)->philos)
		return (ft_error("Error: Failed to allocate philos\n"));
	return (0);
}
//Alloue toutes les struct