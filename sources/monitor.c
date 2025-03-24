/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:16:44 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/24 15:03:35 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&table->meal_mutex);
		if ((get_current_time_ms() - table->philos[i].last_meal_time) \
		> table->time_to_die)
		{
			printf("Time: %lld, Philosopher %d died 💀\n", \
			get_current_time_ms() - table->start_time, table->philos[i].id);
			pthread_mutex_unlock(&table->meal_mutex);
			exit(EXIT_FAILURE);
			return (NULL);
		}
		pthread_mutex_unlock(&table->meal_mutex);
}

int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (is_dead(&table->philos[i]))
		{
			handle_message("died", &table->philos[i], table->philos[i].id);
			
		}
		
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	while (1)
	{
		if (check_death(table))
			break ;
		usleep(50);
	}
	return (NULL);
}
