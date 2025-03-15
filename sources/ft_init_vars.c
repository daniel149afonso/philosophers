/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:16 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/15 21:19:55 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_table(t_table **table, char **argv, int argc)
{
	long	nb_philo;

	nb_philo = ft_atol_v2(argv[1]);
	if (ft_alloc_struct_in_table(table, nb_philo) != 0 || !(*table))
	{
		printf("Error: Failed to allocate memory for table.\n");
		exit(1);
	}
	(*table)->nb_philo = nb_philo;
	(*table)->time_to_die = ft_atol_v2(argv[2]);
	(*table)->time_to_eat = ft_atol_v2(argv[3]);
	(*table)->time_to_sleep = ft_atol_v2(argv[4]);
	if (argc == 6)
		(*table)->nb_limit_meals = ft_atol_v2(argv[5]);
}

void	ft_init_forks_and_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->forks[i].fork_id = i;
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		i++;
	}
	pthread_mutex_init(&table->turn_mutex, NULL);
	table->mutex_initialized = 1;
}

void	ft_init_philos_and_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philos[i].last_meal_time = get_current_time_ms();
		table->philos[i].table = table;
		pthread_create(&table->philos[i].thread_id, NULL,
			&start_routine, &table->philos[i]);
		i++;
	}
}

void	monitor_thread(t_table *table)
{
	pthread_create(&table->monitor_thread, NULL, &monitor_routine, table);
}

void	ft_join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}
//INIT TABLE: alloue toutes les struct dans table (t_table, t_philo, t_fork)
//philo et fork sont des pointeur qui prendront l'addresse d'un tableau
//donc ils sont alloue avec la bonne taille (nb de philos)
//puis on leur passe l'addresse des array en question avec la bonne taille
//--------------------------------------------------------------------------
//FT_INIT_FORKS_MUTEX:
//initialise les forks et les mutex de chaque fork et le mutex meal
