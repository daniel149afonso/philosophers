/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/10 19:29:17 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;
	long		nb_philo;
	long		time;

	philo = (t_philo *)arg;
	nb_philo = philo->table->nb_philo;
	// if (philo->meals_counter == philo->table->nb_limit_meals)
	// 	return (NULL);
	printf("Le philo %d commence la journée ☀️\n", philo->id);
	usleep(5000);
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
		sleep(1);
	}
	//Prendre les fourchettes
	//printf("Le philo %d veut manger...\n", philo->id);
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
	sleep(2);
	printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	//Repas temps
	philo->meals_counter++;
	philo->last_meal_time = get_current_time_ms();
	if ((time = get_current_time_ms() - philo->last_meal_time) > philo->table->time_to_die)
	{
		printf("Philosopher %d died ", philo->id);
		exit(EXIT_FAILURE);
	}
	//Dormir et penser
	printf("Le philo %d dort\n", philo->id);
	sleep(2);
	printf("Le philo %d pense 🧠\n", philo->id);
	sleep(2);
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
	return (NULL);
}

void	philosophers(t_table *table)
{
	ft_init_forks_and_mutexes(table);
	ft_init_philos_and_threads(table);
	ft_join_thread(table);
	ft_destroy_mutex(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 6)
	{
		ft_error("Error: Too few arguments!\n", table);
		return (1);
	}
	if (ft_parsing(argv, table))
		return (1);
	ft_init_table(&table, argv, argc);
	if (table->nb_philo < 2)
	{
		ft_error("Error: Minimum 2 philosophers are required.\n", table);
		return (1);
	}
	while (1)
		philosophers(table);
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