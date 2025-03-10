/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:54:12 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/10 19:32:52 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_alloc_struct_in_table(t_table **table, long nb_philo)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
		return (ft_error("Error: Failed to allocate table\n", *table));
	memset(*table, 0, sizeof(t_table));
	(*table)->forks = malloc(sizeof(t_fork) * nb_philo);
	if (!(*table)->forks)
		return (ft_error("Error: Failed to allocate forks\n", *table));
	(*table)->philos = malloc(sizeof(t_philo) * nb_philo);
	if (!(*table)->philos)
		return (ft_error("Error: Failed to allocate philos\n", *table));
	return (0);
}
//Alloue toutes les struct