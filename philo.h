/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:56 by daniel149af       #+#    #+#             */
/*   Updated: 2025/03/04 21:15:39 by daafonso         ###   ########.fr       */
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

//PREVIOUS DEFINITION OF TABLE
typedef struct s_table	t_table;

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
	int		turn;
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_limit_meals;//[5]
	t_fork	*forks; // array forks
	t_philo	*philos; //array philos
}	t_table;


//MAIN
void	*start_routine(void *arg);

//INIT
void	ft_init_table(t_table **table, char **argv, int argc);
void	ft_init_forks_and_mutexes(t_table *table, int i);
void	ft_init_philos_and_threads(t_table *table, int i);
void	ft_join_thread(t_table *table, int i);
void	ft_destroy_mutex(t_table *table, int i);

//ASSIGN ARRAY
void	ft_assign_philos(t_table *table, t_philo *philos);
void	ft_assign_forks(t_table *table, t_fork *forks);

//ALLOCATE
int		ft_alloc_struct_in_table(t_table **table, long nb_philo);

//ERROR
int		ft_error(char *msg);
#endif