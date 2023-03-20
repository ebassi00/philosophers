/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:44:23 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 16:49:13 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_action(t_philo *philo, char *str)
{
	sem_wait(philo->table->writing);
	if (!philo->is_dead)
		printf("[%llu] %d %s\n", get_time() - philo->table->time, \
				philo->id_philo, str);
	sem_post(philo->table->writing);
}

void	upgrade_sleep(uint64_t time, t_philo *philo)
{
	uint64_t	t;

	t = get_time();
	while (!philo->stop)
	{
		if (get_time() - t >= time)
			break ;
		usleep(500);
	}
}
