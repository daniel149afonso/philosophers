/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:27:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/04 01:14:21 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think(t_philo *philo)
{
	handle_message("is thinking 🧠", philo, philo->id);
}

void	dream(t_philo *philo)
{
	handle_message("is sleeping 😴", philo, philo->id);
	ft_usleep(philo->table->time_to_sleep);
}

int	only_one_philo(t_philo *philo)
{
	if (philo->table->nb_philos == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		handle_message("has taken the left fork 🍴", philo, philo->id);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		handle_message("died 💀", philo, philo->id);
		pthread_mutex_lock(&philo->table->death_mutex);
		*philo->dead_routine = true;
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	return (0);
}

void	set_forks_order(t_philo *philo, t_mutex **first, t_mutex **second)
{
	if (philo->id % 2 == 0)
	{
		*first = &philo->right_fork->mutex;
		*second = &philo->left_fork->mutex;
	}
	else
	{
		*first = &philo->left_fork->mutex;
		*second = &philo->right_fork->mutex;
	}
}

void	eat(t_philo *philo)
{
	t_mutex	*first;
	t_mutex	*second;

	first = NULL;
	second = NULL;
	if (only_one_philo(philo))
		return ;
	set_forks_order(philo, &first, &second);
	pthread_mutex_lock(first);
	handle_message("has taken a fork 🍴", philo, philo->id);
	pthread_mutex_lock(second);
	handle_message("has taken a fork 🍴", philo, philo->id);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = true;
	philo->last_meal_time = get_current_time_ms();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	handle_message("is eating 🍝", philo, philo->id);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->table->meal_mutex);
}
