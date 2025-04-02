/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:16 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/02 03:41:38 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_init_table(t_table **table, char **argv, int argc)
{
	long	nb_philos;

	nb_philos = ft_atol_v2(argv[1]);
	if (ft_alloc_struct_in_table(table, nb_philos))
		return (1);
	(*table)->nb_philos = nb_philos;
	(*table)->time_to_die = ft_atol_v2(argv[2]);
	(*table)->time_to_eat = ft_atol_v2(argv[3]);
	(*table)->time_to_sleep = ft_atol_v2(argv[4]);
	if (argc == 6)
		(*table)->nb_limit_meals = ft_atol_v2(argv[5]);
	return (0);
}

void	ft_init_forks_and_mutexes(t_table *table)
{
	pthread_mutex_init(&table->left_mutex, NULL);
	pthread_mutex_init(&table->right_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	table->mutex_initialized = true;
}

void	ft_init_philos_and_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_current_time_ms();
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philos];
		table->philos[i].last_meal_time = get_current_time_ms();
		table->philos[i].dead_routine = &table->dead_routine;
		table->philos[i].table = table;
		if (pthread_create(&table->philos[i].thread_id, NULL, \
			&start_routine, &table->philos[i]))
			ft_error("Error: Failed to create thread", table);
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL, &monitor_routine, table))
		ft_error("Error: Failed to create thread", table);
}

void	ft_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			ft_error("Error: Failed to create thread", table);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}
//FT_INIT TABLE: alloue toutes les struct dans table (t_table, t_philo, t_fork)
//philo et fork sont des pointeur qui prendront l'addresse d'un tableau
//donc ils sont alloue avec la bonne taille (nb de philos)
//puis on leur passe l'addresse des array en question avec la bonne taille
//--------------------------------------------------------------------------
//FT_INIT_PHILO:
//fork[(i + 1)%nb_philo] //pour que la derniere foruchette pointe sur la 1ere
//Creation variable turn stocké direct dans la struct philo
//1er philo impairs mange ensuite pairs, impairs left fork et pairs right fork
//Evite les deadlocks!!!
//ATTENTION: si nb_philo=impair le last philo impair attend un peu avant manger
//--------------------------------------------------------------------------
//FT_INIT_FORKS_MUTEX:
//initialise les forks et les mutex de chaque fork et le mutex meal
//--------------------------------------------------------------------------
//FT_JOIN_THREAD:
//attend la fin des threads philos et monitor avant de passer a la suite
