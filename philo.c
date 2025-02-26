/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/26 16:16:11 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

pthread_mutex_t fork_mutex;

// void    philo(int philo_N, int dieT, int eatT, int sleepT)
// {
//     int fork;
//     // if (philo_N == 1)
//     //     fork
    
// }

void    *philosopher(void *arg)
{
    (void)arg;
    printf("Le philosophe veut manger...\n");
    
    pthread_mutex_lock(&fork_mutex);
    printf("Le philosophe mange 🍝\n");
    sleep(10); // temps du repas
    printf("Le philosophe a fini de manger et repose la fourchette\n");
    pthread_mutex_unlock(&fork_mutex);

    return (NULL);
}

int main(void)
{
    pthread_t   philo1, philo2;
    
    pthread_mutex_init(&fork_mutex, NULL);

    pthread_create(&philo1, NULL, &philosopher, NULL);
    pthread_create(&philo2, NULL, &philosopher, NULL);
    
    pthread_join(philo1, NULL);
    pthread_join(philo2, NULL);

    pthread_mutex_destroy(&fork_mutex);
    // if (argc != 5)
    //     return ;
    // philo(argv[2],argv[3],argv[4],argv[5]);
    return (0);
}