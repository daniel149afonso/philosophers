/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:56 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/03 19:35:36 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <unistd.h> //write, usleep
# include <stdlib.h> // malloc, free
# include <pthread.h> // mutex: init destroy, lock unlock
					// threads: create, join and detach
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX ?????
# include <string.h> //memset

# define INT_MAX			2147483647
# define INT_MAX_LENGTH		10

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
	int					id;
	int					*turn;
	long				meals_counter; //count nb meals eaten
	long				last_meal_time;// time passed after last meal
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_bool				full;//if philo has eaten the max meals
	t_table				*table;
	pthread_t			thread_id;
	pthread_mutex_t		turn_mutex;
}	t_philo;

//TABLE
typedef struct s_table
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_limit_meals;//[5]
	t_fork	*forks; // array forks
	t_philo	*philos; //array philos
}	t_table;

//INIT
void	ft_init_table(t_table *table, char *argv, int argc);

//ERROR
int	ft_error(char *msg);
#endif