/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:49:16 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/04 22:08:35 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_table(t_table **table, char **argv, int argc)
{
	long	nb_philo;

	(void)argc;
	nb_philo = atol(argv[1]); //a checker le depassement de int avec atol
	if (ft_alloc_struct_in_table(table, nb_philo) != 0 || !(*table))
	{
		printf("Error: Failed to allocate memory for table.\n");
		exit(1);
	}
	
	(*table)->nb_philo = nb_philo;
}

void	ft_init_forks_and_mutexes(t_table *table, int i)
{
	while (i < table->nb_philo)
	{
		table->forks[i].fork_id = i;
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		pthread_mutex_init(&table->philos[i].turn_mutex, NULL);
		i++;
	}
}

void	ft_init_philos_and_threads(t_table *table, int i)
{	
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philos[i].table = table;
		pthread_create(&table->philos[i].thread_id, NULL,
			&start_routine, &table->philos[i]);
		i++;
	}
}

void	ft_join_thread(t_table *table, int i)
{
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}

void	ft_destroy_mutex(t_table *table, int i)
{
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		pthread_mutex_destroy(&table->philos[i].turn_mutex);
		i++;
	}
}
//INIT TABLE: alloue toutes les struct dans table (t_table, t_philo, t_fork)
//philo et fork sont des pointeur qui prendront l'addresse d'un tableau 
//donc ils sont alloue avec la bonne taille (nb de philos)
//puis on leur passe l'addresse des array en question avec la bonne taille
//--------------------------------------------------------------------------