/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/18 22:28:06 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	*start_routine(void *arg)
// {
// 	t_philo		*philo;
// 	long		nb_philo;

// 	philo = (t_philo *)arg;
// 	nb_philo = philo->table->nb_philo;
// 	while (1)
// 	{
// 		if (philo->table->nb_limit_meals)
// 			if (philo->meals_counter == philo->table->nb_limit_meals)
// 				break ;
// 		//printf("Philo %d, Meals %ld\n", philo->id, philo->meals_counter);
// 		//Penser
// 		printf("Time: [%lld] Le philo %d pense 🧠\n",
// 			get_current_time_ms() - philo->table->start_time, philo->id);
// 		//Attendre son tour
// 		while (1)
// 		{
// 			long long time_since_last_meal = get_current_time_ms() - philo->last_meal_time;
// 			if (time_since_last_meal > philo->table->time_to_die - 10)
// 			{
// 				printf("⚠️ Philosophe %d va mourir en attente ! Il mange immédiatement.\n", philo->id);
// 				return (NULL);
// 			}
// 			pthread_mutex_lock(&philo->table->turn_mutex);
// 			if ((philo->table->turn == 0 && philo->id % 2 != 0)
// 				|| (philo->table->turn == 1 && philo->id % 2 == 0))
// 			{
// 				pthread_mutex_unlock(&philo->table->turn_mutex);
// 				break ;
// 			}
// 			pthread_mutex_unlock(&philo->table->turn_mutex);
// 			usleep(500);
// 		}

// 		if (philo->id == nb_philo && philo->id % 2 != 0)
// 		{
// 			printf("Le philo %d est le dernier impair et attend...\n", philo->id);
// 			usleep(1000);
// 		}
// 		//Prendre les fourchettes
// 		if (philo->id % 2 != 0)
// 		{
// 			pthread_mutex_lock(&philo->left_fork->mutex);
// 			pthread_mutex_lock(&philo->right_fork->mutex);
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&philo->right_fork->mutex);
// 			pthread_mutex_lock(&philo->left_fork->mutex);
// 		}
// 		printf("Time: [%lld] Le philo %d mange 🍝\n",
// 			get_current_time_ms() - philo->table->start_time, philo->id);
// 		usleep(philo->table->time_to_eat * 1000);
// 		pthread_mutex_unlock(&philo->left_fork->mutex);
// 		pthread_mutex_unlock(&philo->right_fork->mutex);
// 		//printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
// 		//Repas temps
// 		pthread_mutex_lock(&philo->table->meal_mutex);
// 		philo->last_meal_time = get_current_time_ms();
// 		philo->meals_counter++;
// 		pthread_mutex_unlock(&philo->table->meal_mutex);
// 		//Dormir
// 		printf("Time: [%lld] Le philo %d dort 😴\n",
// 			get_current_time_ms() - philo->table->start_time, philo->id);
// 		usleep(philo->table->time_to_sleep * 1000);

// 		//Syncrhonisation des tours
// 		pthread_mutex_lock(&philo->table->turn_mutex);
// 		philo->table->count++;
// 		printf("🔄 Tour actuel : %d | Philosophe %d a fini | count = %d\n", philo->table->turn, philo->id, philo->table->count);

// 		if ((philo->table->turn == 0 && philo->table->count == nb_philo / 2)
// 			|| (philo->table->turn == 1 && philo->table->count == nb_philo / 2))
// 		{
// 			printf("🟢 Changement de tour ! (Nouveau tour : %d)\n", 1 - philo->table->turn);
// 			philo->table->turn = 1 - philo->table->turn;
// 			philo->table->count = 0;
// 		}
// 		pthread_mutex_unlock(&philo->table->turn_mutex);
// 		long long time_since_last_meal = get_current_time_ms() - philo->last_meal_time;

// 		if (time_since_last_meal > philo->table->time_to_die - 10)
// 		{
// 			printf("⚠️ Philosophe %d va mourir ! Il mange immédiatement.\n", philo->id);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }



void	*start_routine(void *arg)
{

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
			pthread_mutex_lock(&table->meal_mutex);
			if ((get_current_time_ms() - table->philos[i].last_meal_time) \
			> table->time_to_die)
			{
				printf("%ld\n", get_current_time_ms() - table->philos[i].last_meal_time);
				//printf("%ld\n", table->philos[i].last_meal_time);
				printf("Time: %lld, Philosopher %d died 💀\n", \
				get_current_time_ms() - table->start_time, table->philos[i].id);
				pthread_mutex_unlock(&table->meal_mutex);
				exit(EXIT_FAILURE);
				return (NULL);
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
