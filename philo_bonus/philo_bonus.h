/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:19:37 by ebassi            #+#    #+#             */
/*   Updated: 2022/03/25 16:20:07 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_philo {
	int				id_philo;
	int				left_fork;
	int				right_fork;
	int				nbr_meals;
	int				philo_eating;
	int				stop;
	int				is_dead;
	uint64_t		last_meal;
	struct s_table	*table;
	pthread_t		phil_thread;
	pid_t			pid;
}	t_philo;

typedef struct s_table {
	int				nbr_philo;
	int				nbr_phil_finish;
	int				times_to_eat;
	int				exec_finish;
	uint64_t		eat;
	uint64_t		sleep;
	uint64_t		die;
	uint64_t		time;
	t_philo			**phil;
	sem_t			*forks;
	sem_t			*is_eating;
	sem_t			*writing;
}	t_table;

int			ft_exit(char *str);
int			ft_atoi(char *str);
int			is_integer(char *arg);
t_table		*create_philo(t_table *table, char *argv[]);
t_table		*alloc_table(t_table *table, char *argv[]);
uint64_t	get_time(void);
void		ft_usleep(uint64_t time_in_ms);
int			check_arguments(char *argv[]);
int			handle_args(char *arg);
void		*monitoring(void *data);
void		clear_all(t_table *table);
void		print_action(t_philo *philo, char *str);
void		upgrade_sleep(uint64_t time, t_philo *philo);

#endif