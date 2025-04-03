/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:56 by daniel149af       #+#    #+#             */
/*   Updated: 2025/04/03 22:13:32 by daniel149af      ###   ########.fr       */
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

# define LONG_MAX_LENGTH 19
# define MAX_PHILOS 200

//PREVIOUS DEFINITION OF TABLE: because not init in t_philo struct
typedef struct s_table	t_table;

//REDEFINITION OF MUTEX: because is shorter to use
typedef pthread_mutex_t	t_mutex;

//BOOL
typedef enum s_bool
{
	false,
	true
}	t_bool;

//FORKS
typedef struct s_fork
{
	t_mutex	mutex;
}	t_fork;

//PHILO
typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_table				*table;
	t_bool				*dead_routine;
	t_bool				eating;
	pthread_t			thread_id;
}	t_philo;

//TABLE
typedef struct s_table
{
	long		nb_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nb_limit_meals;
	long long	start_time;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor_thread;
	t_mutex		death_mutex;
	t_mutex		meal_mutex;
	t_mutex		write_mutex;
	t_bool		dead_routine;
	t_bool		mutex_initialized;
}	t_table;

//MAIN
void	*start_routine(void *arg);

//INIT
int		ft_init_table(t_table **table, char **argv, int argc);
void	ft_init_forks_and_mutexes(t_table *table);
void	ft_init_philos(t_table *table);
void	ft_create_thread(t_table *table);
void	ft_join_threads(t_table *table);

//ROUTINE ACTIONS
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

//MONITOR
void	*monitor_routine(void *arg);
int		stop_routine(t_philo *philo);

//ALLOCATE
int		ft_alloc_struct_in_table(t_table **table, long nb_philo);

//PARSING
int		ft_parsing(char **argv, t_table *table);
long	ft_atol_v2(const char *str);
int		is_number(char **strs);

//FREE AND ERROR
int		ft_error(char *msg, t_table *table);
void	ft_free_table(t_table *table);
void	ft_destroy_mutex(t_table *table);

//UTILS
long	get_current_time_ms(void);
void	ft_usleep(long time_ms);
void	handle_message(char *msg, t_philo *philo, int id);

#endif
