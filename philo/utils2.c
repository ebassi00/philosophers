/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:44:23 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 16:49:43 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(char *argv[])
{
	int	i;

	i = 0;
	if (ft_atoi(argv[0]) < 1 || ft_atoi(argv[0]) > 200)
		return (0);
	if (ft_atoi(argv[1]) < 60 || ft_atoi(argv[2]) < 60)
		return (0);
	if (ft_atoi(argv[3]) < 60)
		return (0);
	if (argv[4])
	{
		if (ft_atoi(argv[4]) <= 0)
			return (0);
	}
	return (1);
}

int	handle_args(char *arg)
{
	if (!is_integer(arg))
		return (0);
	return (1);
}

void	clear_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		free(table->phil[i]);
		i++;
	}
	free(table->phil);
	free(table->forks);
	pthread_mutex_destroy(&table->death);
	pthread_mutex_destroy(&table->finish);
	pthread_mutex_destroy(&table->is_eating);
	pthread_mutex_destroy(&table->message);
	pthread_mutex_destroy(table->forks);
	free(table);
}
