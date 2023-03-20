/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:56 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/24 16:33:12 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->message);
	printf("[%llu] %d is sleeping\n", get_time() - philo->table->time, \
			philo->id_philo);
	pthread_mutex_unlock(&philo->table->message);
	usleep(philo->table->sleep * 1000);
	while ((get_time() - philo->table->time) - philo->last_meal \
			< philo->table->sleep)
		continue ;
	pthread_mutex_lock(&philo->table->message);
	printf("[%llu] %d is thinking\n", get_time() - philo->table->time, \
			philo->id_philo);
	pthread_mutex_unlock(&philo->table->message);
}

void	activity(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->is_eating);
	philo->last_meal = get_time() - philo->table->time;
	philo->nbr_meals++;
	if (philo->nbr_meals == philo->table->times_to_eat)
		philo->table->nbr_phil_finish++;
	pthread_mutex_unlock(&philo->table->is_eating);
	usleep(philo->table->eat * 1000 - 20000);
	while ((get_time() - philo->table->time) - philo->last_meal \
			< philo->table->eat)
		continue ;
	pthread_mutex_unlock(&philo->table->forks[philo->id_philo - 1]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id_philo) \
						% philo->table->nbr_philo]);
	philo->philo_eating = 0;
	sleep_think(philo);
}

void	*start_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	while (!philo->table->is_dead)
	{
		pthread_mutex_lock(&philo->table->forks[philo->id_philo - 1]);
		pthread_mutex_lock(&philo->table->message);
		printf("[%llu] %d has taken a fork\n", get_time() - philo->table->time, \
				philo->id_philo);
		pthread_mutex_unlock(&philo->table->message);
		pthread_mutex_lock(&philo->table->forks[(philo->id_philo) \
							% philo->table->nbr_philo]);
		pthread_mutex_lock(&philo->table->message);
		printf("[%llu] %d has taken a fork\n", get_time() - philo->table->time, \
				philo->id_philo);
		pthread_mutex_unlock(&philo->table->message);
		philo->philo_eating = 1;
		pthread_mutex_lock(&philo->table->message);
		printf("[%llu] %d is eating\n", get_time() - philo->table->time, \
				philo->id_philo);
		pthread_mutex_unlock(&philo->table->message);
		activity(philo);
	}
	return (NULL);
}

void	phil_thread(t_table *table)
{
	int	i;

	i = 0;
	while (!table->is_dead)
	{
		while (i < table->nbr_philo)
		{
			pthread_create(&table->phil[i]->phil_thread, NULL, start_dinner, \
							(void *)table->phil[i]);
			i++;
			usleep(100);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_table		*table;
	pthread_t	thread;
	int			i;

	i = 1;
	table = 0;
	if (argc < 4 || argc > 6)
		return (ft_exit("Wrong number of arguments"));
	if (!check_arguments(&argv[1]))
		return (ft_exit("Wrong arguments"));
	table = alloc_table(table, argv);
	i = -1;
	while (++i < table->nbr_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_create(&thread, NULL, monitoring, table);
	phil_thread(table);
	clear_all(table);
	return (1);
}
