/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/20 16:23:51 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		think(philo);
		eat(philo);
		dream(philo);
	}
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (!table->philos[i].eating)
			{
				pthread_mutex_lock(&table->meal_mutex);
				if ((get_current_time_ms() - table->philos[i].last_meal_time) \
				> table->time_to_die)
				{
					//printf("%ld\n", get_current_time_ms() - table->philos[i].last_meal_time);
					//printf("%ld\n", table->philos[i].last_meal_time);
					printf("Time: %lld, Philosopher %d died 💀\n", \
					get_current_time_ms() - table->start_time, table->philos[i].id);
					pthread_mutex_unlock(&table->meal_mutex);
					exit(EXIT_FAILURE);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&table->meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	stop_routine(t_table *table)
{
	ft_join_thread(table);
	ft_free_table(table);
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
	monitor_thread(table);
	stop_routine(table);
	return (0);
}
//Rappel : Un mutex protège une section de code, pas une variable
//Un mutex est un verrou qui empêche plusieurs threads de lire ou modifier
//en même temps une variable partagée (c'est chacun son tour: sequentiel)
//Evite condition races (tout le monde veut faire la meme chose a un instant)
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
