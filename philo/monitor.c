/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:58 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 16:49:07 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->death);
	pthread_mutex_lock(&table->message);
	printf("[%llu] %d died\n", get_time() - table->time, \
			table->phil[i]->id_philo);
	table->is_dead = 1;
}

void	*monitoring(void *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *) data;
	while (!table->is_dead)
	{
		i = -1;
		while (++i < table->nbr_philo)
		{
			if (table->nbr_phil_finish == table->nbr_philo)
			{
				table->is_dead = 1;
				break ;
			}
			if ((get_time() - table->time) - table->phil[i]->last_meal \
				>= table->die && !table->phil[i]->philo_eating)
			{
				handle_death(table, i);
				break ;
			}
		}
	}
	return (NULL);
}
