/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:56 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/26 19:36:44 by daniel149af      ###   ########.fr       */
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
}  t_bool;

//MUTEX
typedef pthread_mutex_t t_mtx;

//FORK
typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;
}   t_fork;

//PHILO
typedef struct s_philo
{
    int     id;
    long    meals_counter;
    t_bool  full;
    long    last_meal_time; // time passed after last meal
    t_fork  left_fork;
    t_fork  right_fork;
    pthread_t   thread_id; // a philo is a thread
}   t_philo;
#endif