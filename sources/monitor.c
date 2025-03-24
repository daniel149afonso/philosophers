/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:16:44 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/24 19:46:28 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	if ((get_current_time_ms() - philo->last_meal_time)
		> philo->table->time_to_die && philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->table->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (0);
}

int	check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (is_dead(&table->philos[i]))
		{
			handle_message("died 💀", &table->philos[i], table->philos[i].id);
			pthread_mutex_lock(&table->death_mutex);
			table->philos[i].dead = 1;
			pthread_mutex_unlock(&table->death_mutex);
			pause();
		}
		i++;
	}
	return (0);
}

// int	check_meals(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (1)
// 	{
// 		/* code */
// 	}

// }

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_death(table))
			break ;
		usleep(50);
	}
	return (NULL);
}
