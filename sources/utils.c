/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:50:01 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/24 18:14:52 by daafonso         ###   ########.fr       */
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

	current = get_current_time_ms() - philo->table->start_time;
	printf("Time: [%lld] %d %s\n", current, id, msg);
}
