/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/13 00:53:19 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;
	long		nb_philo;

	philo = (t_philo *)arg;
	nb_philo = philo->table->nb_philo;
	while (1)
	{
		printf("Philo %d, Meals %ld\n", philo->id, philo->meals_counter);
		if (philo->meals_counter == philo->table->nb_limit_meals)
			break ;
		//Attendre son tour
		while (1)
		{
			pthread_mutex_lock(&philo->table->turn_mutex);
			if ((philo->table->turn == 0 && philo->id % 2 != 0)
				|| (philo->table->turn == 1 && philo->id % 2 == 0))
			{
				pthread_mutex_unlock(&philo->table->turn_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->table->turn_mutex);
			usleep(5000);
		}
		if (philo->id == nb_philo && philo->id % 2 != 0)
		{
			printf("Le philo %d est le dernier impair et attend...\n", philo->id);
			usleep(5000);
		}
		//Prendre les fourchettes
		if (philo->id % 2 != 0)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->right_fork->mutex);
			pthread_mutex_lock(&philo->left_fork->mutex);
		}
		printf("Le philo %d mange 🍝\n", philo->id);
		sleep(philo->table->time_to_eat);
		printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		//Repas temps
		philo->meals_counter++;
		philo->last_meal_time = get_current_time_ms();
		//Dormir et penser
		printf("Le philo %d dort\n", philo->id);
		sleep(2);
		printf("Le philo %d pense 🧠\n", philo->id);
		//Syncrhonisation des tours
		pthread_mutex_lock(&philo->table->turn_mutex);
		philo->table->count++;
		if ((philo->id % 2 != 0 && philo->table->turn == 0 && philo->table->count == (nb_philo + 1) / 2)
			|| (philo->id % 2 == 0 && philo->table->turn == 1 && philo->table->count == nb_philo / 2))
		{
			philo->table->turn = 1 - philo->table->turn; // 🔄 Change le tour
			philo->table->count = 0;
		}
		pthread_mutex_unlock(&philo->table->turn_mutex);
		monitor(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	while (1)
	{
		while (i < table->nb_philo)
		{
			if ((get_current_time_ms() - table->philos[i].last_meal_time) \
			> table->time_to_die)
			{
				printf("Time: %ld, Philosopher %d died\n",
					get_current_time_ms(), table->philos[i].id);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	monitor_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].id, NULL, &monitor, &table->philos[i]);
	}

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
	ft_join_thread(table);
	ft_free_table(table);
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