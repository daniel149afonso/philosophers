void	*start_routine(void *arg)
{
	t_philo		*philo;
	long		nb_philo;

	philo = (t_philo *)arg;
	nb_philo = philo->table->nb_philo;
	while (1)
	{
		if (philo->table->nb_limit_meals)
			if (philo->meals_counter == philo->table->nb_limit_meals)
				break ;
		//printf("Philo %d, Meals %ld\n", philo->id, philo->meals_counter);
		//Penser
		printf("Time: [%lld] Le philo %d pense 🧠\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
		//Attendre son tour
		while (1)
		{
			long long time_since_last_meal = get_current_time_ms() - philo->last_meal_time;
			if (time_since_last_meal > philo->table->time_to_die - 10)
			{
				printf("⚠️ Philosophe %d va mourir en attente ! Il mange immédiatement.\n", philo->id);
				return (NULL);
			}
			pthread_mutex_lock(&philo->table->turn_mutex);
			if ((philo->table->turn == 0 && philo->id % 2 != 0)
				|| (philo->table->turn == 1 && philo->id % 2 == 0))
			{
				pthread_mutex_unlock(&philo->table->turn_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->table->turn_mutex);
			usleep(500);
		}

		if (philo->id == nb_philo && philo->id % 2 != 0)
		{
			printf("Le philo %d est le dernier impair et attend...\n", philo->id);
			usleep(1000);
		}
		//Prendre les fourchettes
		if (philo->id % 2 != 0)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->right_fork->mutex);
			pthread_mutex_lock(&philo->left_fork->mutex);
		}
		printf("Time: [%lld] Le philo %d mange 🍝\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		//printf("Le philo %d a fini de manger et repose la fourchette\n", philo->id);
		//Repas temps
		pthread_mutex_lock(&philo->table->meal_mutex);
		philo->last_meal_time = get_current_time_ms();
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->table->meal_mutex);
		//Dormir
		printf("Time: [%lld] Le philo %d dort 😴\n",
			get_current_time_ms() - philo->table->start_time, philo->id);
		ft_usleep(philo->table->time_to_sleep);
		//Syncrhonisation des tours
		pthread_mutex_lock(&philo->table->turn_mutex);
		philo->table->count++;
		printf("🔄 Tour actuel : %d | Philosophe %d a fini | count = %d\n", philo->table->turn, philo->id, philo->table->count);

		if ((philo->table->turn == 0 && philo->table->count == nb_philo / 2)
			|| (philo->table->turn == 1 && philo->table->count == nb_philo / 2))
		{
			printf("🟢 Changement de tour ! (Nouveau tour : %d)\n", 1 - philo->table->turn);
			philo->table->turn = 1 - philo->table->turn;
			philo->table->count = 0;
		}
		pthread_mutex_unlock(&philo->table->turn_mutex);
		long long time_since_last_meal = get_current_time_ms() - philo->last_meal_time;

		if (time_since_last_meal > philo->table->time_to_die - 10)
		{
			printf("⚠️ Philosophe %d va mourir ! Il mange immédiatement.\n", philo->id);
			return (NULL);
		}
	}
	return (NULL);
}