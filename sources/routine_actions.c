/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:27:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/09 18:42:15 by daniel149af      ###   ########.fr       */
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

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	handle_message("has taken a fork 🍴", philo, philo->id);
	if (philo->table->nb_philos == 1)
	{
		ft_usleep(philo->table->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	handle_message("has taken a fork 🍴", philo, philo->id);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = true;
	philo->last_meal_time = get_current_time_ms();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	handle_message("is eating 🍝", philo, philo->id);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->table->meal_mutex);
}
