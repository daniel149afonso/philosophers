/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:27:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/03/19 16:39:58 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think(t_philo *philo)
{
	handle_message("is thinking 🧠", philo, philo->id);
}

// Dream routine funtion

void	dream(t_philo *philo)
{
	handle_message("is sleeping 😴", philo, philo->id);
	ft_usleep(philo->table->time_to_sleep);
}

// Eat routine funtion

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	handle_message("has taken the left fork", philo, philo->id);
	pthread_mutex_lock(&philo->right_fork->mutex);
	handle_message("has taken the right fork", philo, philo->id);
	philo->eating = 1;
	handle_message("is eating 🍝", philo, philo->id);
	ft_usleep(philo->table->time_to_eat);
	//MEAL
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	//FIN MEAL 
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->eating = 0;
}
