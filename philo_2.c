/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/27 19:58:28 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Le philo %d pense 🧠\n", philo->id);
	sleep(6);
	printf("Le philo %d veut manger...\n", philo->id);
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	printf("Le philo %d mange 🍝\n", philo->id);
	sleep(6);
	printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	printf("Le philo %d dort\n", philo->id);
	sleep(6);
	printf("Le philo %d a fini de dormir\n", philo->id);
	return (NULL);
}

void	create_philo(int nb_philo)
{
	int		i;
	t_philo	philo[nb_philo];
	t_fork	fork[nb_philo];

	i = 0;
	while (i < nb_philo)
	{
		fork[i].fork_id = i;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % nb_philo];
		pthread_create(&philo[i].thread_id, NULL, &philosophers, &philo[i]);
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
	int	nb;

	(void)argc;
	if (argc != 2)
	{
		printf("Number of philosophers is required!\n");
		return (1);
	}
	nb = atoi(argv[1]);//ATTENTION ne prend pas en compte les overflow de int 
	printf("%d\n", nb);
	while (1)
	{
		create_philo(nb);
	}
	return (0);
}
//fork[(i + 1)% nb_philo] //pour que la derniere foruchette pointe sur la 1ere