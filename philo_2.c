/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:20 by daniel149af       #+#    #+#             */
/*   Updated: 2025/02/26 19:42:19 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

pthread_mutex_t fork_mutex;

void    *philosophers(void *arg)
{
    int id = *(int *)arg;
    printf("Le philosophe %d veut manger...\n", id);
    
    pthread_mutex_lock(&fork_mutex);
    printf("Le philosophe %d mange 🍝\n", id);
    sleep(5); // temps du repas
    printf("Le philosophe %d a fini de manger et repose la fourchette\n", id);
    pthread_mutex_unlock(&fork_mutex);

    return (NULL);
}

void    create_philo(int nb)
{
    t_philo philo;

    for (int i = 0; i < nb; i++)
    {
        
        pthread_create(&philosopher[i], NULL, &philosophers, &ids[i]);
    }
    
    for (int i = 0; i < nb; i++)
    {
        pthread_join(philosopher[i], NULL);
    }
    
}

int main(int argc, char **argv)
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