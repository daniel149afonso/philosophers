/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/29 02:42:49 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_current_time_ms(void)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(long time_ms)
{
	long	time_us;

	time_us = time_ms * 1000;
	usleep(time_us);
}

long long	elapsed_time(long long time)
{
	return (get_current_time_ms() - time);
}

void	handle_message(char *msg, t_philo *philo, int id)
{
	long long	current;

	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->dead_routine == true)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->table->write_mutex);
	current = get_current_time_ms() - philo->table->start_time;
	printf("Time: [%lld] %d %s\n", current, id, msg);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
