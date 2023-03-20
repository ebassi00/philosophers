/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:44:57 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 15:41:38 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		table->phil[i]->is_dead = 0;
		table->phil[i]->stop = 0;
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
	table->nbr_phil_finish = 0;
	table->exec_finish = 0;
	table->time = get_time();
	table = create_philo(table, &argv[1]);
	sem_unlink("sem_forks");
	sem_unlink("sem_write");
	sem_unlink("sem_eating");
	table->forks = sem_open("sem_forks", O_CREAT, 0644, table->nbr_philo);
	table->writing = sem_open("sem_write", O_CREAT, 0644, 1);
	table->is_eating = sem_open("sem_eating", O_CREAT, 0644, 1);
	return (table);
}
