/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/26 22:31:25 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t fork_mutex;

void	*philosophers(void *arg)
{
	int	*id;

	id = NULL;
	id = (int *)arg;
	printf("Le philosophe %d veut manger...\n", (*id));
	pthread_mutex_lock(&fork_mutex);
	printf("Le philosophe %d mange 🍝\n", (*id));
	sleep(5);
	printf("Le philosophe %d a fini de manger et repose la fourchette\n", (*id));
	pthread_mutex_unlock(&fork_mutex);
	return (NULL);
}

void	create_philo(int nb_philo)
{
	t_philo	philo[nb_philo];
	int		i;
	int		nb_fork;

	i = 0;
	nb_fork = nb_philo ;
	while (i < nb_philo)
	{
		philo[i].id = i;
		pthread_create(&philo[i].thread_id, NULL, &philosophers, &philo[i].id);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	int  nb = atoi(argv[1]);
	while (1)
	{
		create_philo(nb);
	}
	pthread_mutex_destroy(&fork_mutex);
	return (0);
}