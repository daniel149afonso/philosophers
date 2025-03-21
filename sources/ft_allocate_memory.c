/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:54:12 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/20 23:03:41 by daniel149af      ###   ########.fr       */
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
		return (ft_error("Error: Failed to allocate fork array\n", *table));
	(*table)->philos = malloc(sizeof(t_philo) * nb_philo);
	if (!(*table)->philos)
		return (ft_error("Error: Failed to allocate philo array\n", *table));
	return (0);
}
//BUT: Allouer les struct table, forks(array) et philos(array)
//Memset: initialise toutes les valeurs des champs table à 0 dans notre cas