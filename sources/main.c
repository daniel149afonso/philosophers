/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/24 19:44:23 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(5);
	while (!death_flag(philo))
	{
		think(philo);
		eat(philo);
		dream(philo);
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
	if (ft_parsing(argv, table))
		return (1);
	ft_init_table(&table, argv, argc);
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
//FT_INIT_PHILO:
//fork[(i + 1)%nb_philo] //pour que la derniere foruchette pointe sur la 1ere
//Creation variable turn stocké direct dans la struct philo
//1er philo impairs mange ensuite pairs, impairs left fork et pairs right fork
//Evite les deadlocks!!!
//ATTENTION: si nb_philo=impair le last philo impair attend un peu avant manger
//--------------------------------------------
//Start Routine:
//On bloque le turn mutex pour eviter que plusieur philo modif en meme temps
//Pourquoi 2 déverrouillages (pthread_mutex_unlock) ?
//1er unlock: Si le philosophe peut manger, il sort de la boucle immédiatement
//2eme unlock: Si c'est pas son tour il laisse les autres threads modifier turn
