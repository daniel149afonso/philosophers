/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:27:35 by daafonso          #+#    #+#             */
/*   Updated: 2025/04/03 16:30:09 by daniel149af      ###   ########.fr       */
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

// int	only_one_philo(t_philo *philo)
// {
// 	if (philo->table->nb_philos == 1)
// 	{
// 		pthread_mutex_lock(&philo->left_fork->mutex);
// 		handle_message("has taken the left fork 🍴", philo, philo->id);
// 		pthread_mutex_unlock(&philo->left_fork->mutex);
// 		handle_message("died 💀", philo, philo->id);
// 		pthread_mutex_lock(&philo->table->death_mutex);
// 		*philo->dead_routine = true;
// 		pthread_mutex_unlock(&philo->table->death_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// void	take_forks(t_philo *philo)
// {

// }

void	eat(t_philo *philo)
{
	//ajouter condition pour un philo + changer la structure des fork et mutex
	pthread_mutex_lock(&philo->left_fork->mutex);
	handle_message("has taken the left fork 🍴", philo, philo->id);
	pthread_mutex_lock(&philo->right_fork->mutex);
	handle_message("has taken the right fork 🍴", philo, philo->id);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = true;
	philo->last_meal_time = get_current_time_ms();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	handle_message("is eating 🍝", philo, philo->id);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->table->meal_mutex);
}
