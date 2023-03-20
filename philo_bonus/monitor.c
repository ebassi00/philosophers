/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:58 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 16:21:23 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_death(t_philo *philo)
{
	philo->is_dead = 1;
	sem_wait(philo->table->writing);
	printf("[%llu] %d died\n", get_time() - philo->table->time, \
			philo->id_philo);
	philo->stop = 1;
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	while (!philo->stop)
	{
		usleep(100);
		if ((get_time() - philo->table->time) - philo->last_meal \
			>= philo->table->die && !philo->philo_eating)
		{
			handle_death(philo);
			break ;
		}
		if (philo->table->times_to_eat != -1 && \
			philo->nbr_meals == philo->table->times_to_eat)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->is_dead)
		exit(1);
	else
		exit(0);
	return (NULL);
}
