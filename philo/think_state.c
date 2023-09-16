/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:27:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/16 18:49:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <unistd.h>
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

// int	right(int i, t_data *data);
// int	left(int i, t_data *data);

#include <stdio.h>
// static inline void	odd_adjustment(bool *even)
// {
// 	even = true;
// 	usleep(100);
// 	printf("swapped\n");
// }

bool	death_check(t_philo *philo, struct timeval time)
{
	struct timeval	starvation_time;

	starvation_time = \
	timeval_add_su(philo->last_meal, philo->data->time_to_die * MILLISEC);
	if (time_su_subtract(starvation_time, time) <= 0)
	{
		change_state(philo, Dead, time);
		return (true);
	}
	return (false);
}

bool	fork_struggle(t_philo *philo, int fork_n)
{
	bool			fork;
	struct timeval	time;

	fork = false;
	while (!fork)
	{
		gettimeofday(&time, NULL);
		if (death_check(philo, time))
			return (false);
		fork = pick_up_fork(philo->data, fork_n);
	}
	return (true);
}

void	think_state(t_philo *philo)
{
	struct timeval	time;
	int				fork[2];
	bool			even;

	fork[0] = philo->n - 1;
	fork[1] = philo->n % philo->data->n_philo;
	even = !(philo->n & 1);
	if (philo->data->n_philo & 1 \
	&& philo->n == philo->data->n_philo && !(philo->meal_count & 1))
		even = true;
	if (even)
		usleep(100);
	if (!fork_struggle(philo, fork[even]))
		return ;
	gettimeofday(&time, NULL);
	if (check_all_alive(philo->data))
		p_log_state_change(philo->n, Taking_fork, \
		philo->data->start_time, time);
	if (!fork_struggle(philo, fork[!even]))
		return ;
	gettimeofday(&time, NULL);
	if (check_all_alive(philo->data))
		p_log_state_change(philo->n, Taking_fork, \
		philo->data->start_time, time);
	change_state(philo, Eating, time);
}

/*void	_think_state(t_philo *philo)
{
	int				*table;
	pthread_mutex_t	*table_lock;
	struct timeval	time;
	bool			taken_both_forks;

	gettimeofday(&time, NULL);
	if (death_check(philo, time))
		return ;
	table = philo->data->table;
	table_lock = &philo->data->table_lock;
	taken_both_forks = false;
	pthread_mutex_lock(table_lock);
	if (table[philo->n - 1] && table[philo->n % philo->data->n_philo])
	{
		table[philo->n - 1] = 0;
		table[philo->n % philo->data->n_philo] = 0;
		taken_both_forks = (philo->data->n_philo > 1);
		p_log_state_change(philo->n, Taking_fork - (philo->data->n_philo > 1), 
		philo->data->start_time, time);
	}
	pthread_mutex_unlock(table_lock);
	if (taken_both_forks)
		change_state(philo, Eating, time);
}*/

// void	think_state(t_philo *philo)
// {
// 	struct timeval	time;
// 	pthread_mutex_t	*locks[3];

// 	locks[0] = &philo->data->fork_lock[left(philo->n, philo->data)];
// 	locks[1] = &philo->data->fork_lock[philo->n - 1];
// 	locks[2] = &philo->data->fork_lock[right(philo->n, philo->data)];
// 	while (philo->state == Thinking)
// 	{
// 		// usleep(50 * (philo->n - 1));
// 		gettimeofday(&time, NULL);
// 		if (death_check(philo, time))
// 			break ;
// 		pthread_mutex_lock(locks[0]);
// 		pthread_mutex_lock(locks[1]);
// 		pthread_mutex_lock(locks[2]);

// 	}
// }
