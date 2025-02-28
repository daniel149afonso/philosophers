/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:56 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/27 19:45:24 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <unistd.h> //write, usleep
# include <stdlib.h> // malloc free
# include <pthread.h> // mutex: init destroy, lock unlock
					// threads: create, join and detach
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX

//BOOL
typedef enum s_bool
{
	false,
	true
}	t_bool;

//FORK
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

//PHILO
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	long		meals_counter;
	t_bool		full;
	long		last_meal_time;
}	t_philo;
#endif