/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/01 21:14:54 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_routine(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5)
	{
		ft_error("Error: Only [number philosophers], [time_death], [time_eat],"
			" [time_sleep], optional [number meals] are required!\n", table);
		return (1);
	}
	if (ft_parsing(argv, table) || ft_init_table(&table, argv, argc))
		return (1);
	ft_init_forks_and_mutexes(table);
	ft_init_philos_and_threads(table);
	ft_join_threads(table);
	ft_free_table(table);
	return (0);
}
//Rappel : Un mutex protège une section de code, pas une variable
//Un mutex est un verrou qui empêche plusieurs threads de lire ou modifier
//en même temps une variable partagée (c'est chacun son tour: sequentiel)
//Evite rat races (tout le monde veut faire la meme chose a un instant)
//-----------------------------------------------------------
//Start Routine:
//Les philos pairs commence en retard pour laisser les impairs manger d'abord
//Contribue a eviter les deadlocks
