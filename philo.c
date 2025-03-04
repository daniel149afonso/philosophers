/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/04 03:43:52 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *arg)
{
	t_philo		*philo;
	static int	count = 0;

	philo = (t_philo *)arg;
	printf("Le philo %d pense 🧠\n", philo->id);
	sleep(6);
	while (1)
	{
		pthread_mutex_lock(&philo->turn_mutex);
		if ((*philo->turn == 0 && philo->id % 2 == 0)
			|| (*philo->turn == 1 && philo->id % 2 != 0))
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
	if ((philo->id % 2 == 0 && *philo->turn == 0 && count == (philo->nb_philo + 1) / 2) \
	|| (philo->id % 2 != 0 && *philo->turn == 1 && count == philo->nb_philo / 2)) 
	{
		*philo->turn = 1 - *philo->turn; // 🔄 Change le tour
		count = 0;
	}
	pthread_mutex_unlock(&philo->turn_mutex);
	return (NULL);
}

void	ft_create_philo(t_table *table)
{
	int				i;
	int				turn;
	t_philo			philo[table->nb_philo];
	t_fork			forks[table->nb_philo];

	turn = 0;
	i = 0;
	while (i < table->nb_philo)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].mutex, NULL);
		pthread_mutex_init(&philo[i].turn_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % table->nb_philo];
		philo[i].turn = &turn;
		pthread_create(&philo[i].thread_id, NULL, &start_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		pthread_mutex_destroy(&philo[i].turn_mutex);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_error("Error: Failed to allocate table\n"));
	memset(table, 0, sizeof(t_table));
	if (argc < 2)
	{
		printf("Error: Number of philosophers is required!\n");
		return (1);
	}
	ft_init_table(table, argv, argc);
	if (table->nb_philo < 2)
	{
		printf("Error: Minimum 2 philosophers are required.\n");
		return (1);
	}
	while (1)
		ft_create_philo(table);
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