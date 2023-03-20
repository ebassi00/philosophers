/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:44:57 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/24 14:51:09 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_philo(t_table *table, char *argv[])
{
	int	nbr_philo;
	int	i;

	i = 0;
	nbr_philo = ft_atoi(argv[0]);
	table->phil = malloc (sizeof(t_philo) * nbr_philo);
	while (i < nbr_philo)
	{
		table->phil[i] = malloc (sizeof(t_philo));
		table->phil[i]->id_philo = i + 1;
		table->phil[i]->table = table;
		table->phil[i]->left_fork = 0;
		table->phil[i]->right_fork = 0;
		table->phil[i]->last_meal = 0;
		table->phil[i]->philo_eating = 0;
		table->phil[i]->nbr_meals = 0;
		i++;
	}
	return (table);
}

t_table	*alloc_table(t_table *table, char *argv[])
{
	table = malloc (sizeof(t_table));
	table->nbr_philo = ft_atoi(argv[1]);
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->times_to_eat = ft_atoi(argv[5]);
	else
		table->times_to_eat = -1;
	table->is_dead = 0;
	table->nbr_phil_finish = 0;
	table->exec_finish = 0;
	table->time = get_time();
	table = create_philo(table, &argv[1]);
	table->forks = malloc (sizeof(pthread_mutex_t) * table->nbr_philo);
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->finish, NULL);
	pthread_mutex_init(&table->is_eating, NULL);
	pthread_mutex_init(&table->message, NULL);
	return (table);
}
