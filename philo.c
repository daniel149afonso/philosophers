/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/04 21:38:05 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;
	static int	count = 0;
	long		nb_philo;

	philo = (t_philo *)arg;
	nb_philo = philo->table->nb_philo;
	printf("Le philo %d pense 🧠\n", philo->id);
	sleep(6);
	while (1)
	{
		pthread_mutex_lock(&philo->turn_mutex);
		if ((philo->table->turn == 0 && philo->id % 2 == 0)
			|| (philo->table->turn == 1 && philo->id % 2 != 0))
		{
			pthread_mutex_unlock(&philo->turn_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->turn_mutex);
		sleep(6);
	}
	printf("Le philo %d veut manger...\n", philo->id);
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	printf("Le philo %d mange 🍝\n", philo->id);
	sleep(6);
	printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	printf("Le philo %d dort\n", philo->id);
	sleep(6);
	pthread_mutex_lock(&philo->turn_mutex);
	count++;
	if ((philo->id % 2 == 0 && philo->table->turn == 0 && count == (nb_philo + 1) / 2)
		|| (philo->id % 2 != 0 && philo->table->turn == 1 && count == nb_philo / 2))
	{
		philo->table->turn = 1 - philo->table->turn; // 🔄 Change le tour
		count = 0;
	}
	pthread_mutex_unlock(&philo->turn_mutex);
	return (NULL);
}

void	philosophers(t_table *table)
{
	int				i;

	i = 0;
	ft_init_forks_and_mutexes(table, i);
	ft_init_philos_and_threads(table, i);
	ft_join_thread(table, i);
	ft_destroy_mutex(table, i);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 2)
	{
		printf("Error: Number of philosophers is required!\n");
		return (1);
	}
	ft_init_table(&table, argv, argc);
	if (table == NULL)
	{
		printf("Table est NULL");
		exit(EXIT_FAILURE);
	}
	if (table->nb_philo < 2)
	{
		printf("Error: Minimum 2 philosophers are required.\n");
		return (1);
	}
	while (1)
		philosophers(table);
	return (0);
}
//Rappel : Un mutex protège une section de code, pas une variable
//Un mutex est un verrou qui empêche plusieurs threads d’accéder ou modifier
//en même temps à une variable partagée (c'est chacun son tour)
//fork[(i + 1)%nb_philo] //pour que la derniere foruchette pointe sur la 1ere
//Creation variable turn stocké direct dans la struct philo
//1er philo pairs mange ensuite impairs
//Evite la famine pour cause d'attente prolongée
//--------------------------------------------
//Start Routine:
//On bloque le turn mutex pour eviter que plusieur philo modif en meme temps
//Pourquoi 2 déverrouillages (pthread_mutex_unlock) ?
//1er unlock: Si le philosophe peut manger, il sort de la boucle immédiatement
//2eme unlock: Si c'est pas son tour il laisse les autres threads modifier turn