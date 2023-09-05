/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:26:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/05 17:52:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include "time/ft_time.h"
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

bool	pick_up_fork(t_data *data, int fork_n)
{
	bool	success;

	success = false;
	pthread_mutex_lock(&data->fork_lock[fork_n]);
	if (data->table[fork_n])
	{
		data->table[fork_n] = 0;
		success = true;
	}
	pthread_mutex_unlock(&data->fork_lock[fork_n]);
	return (success);
}

bool	put_down_fork(t_data *data, int fork_n)
{
	bool	success;

	success = false;
	pthread_mutex_lock(&data->fork_lock[fork_n]);
	if (!data->table[fork_n])
	{
		data->table[fork_n] = 1;
		success = true;
	}
	pthread_mutex_unlock(&data->fork_lock[fork_n]);
	return (success);
}

void	change_state(t_philo *philo, enum e_philo_state new_state, \
struct timeval time)
{
	if (new_state != Dead && check_all_alive(philo->data))
		p_log_state_change(philo->n, new_state, philo->data->start_time, time);
	if (new_state == Eating)
	{
		philo->last_meal = time;
		philo->meal_count++;
		if (philo->meal_count == philo->data->times_philo_must_eat)
		{
			put_down_forks(philo);
			new_state = Dead;
		}
	}
	else if (new_state == Dead)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->all_alive)
			p_log_state_change(philo->n, new_state, \
			philo->data->start_time, time);
		philo->data->all_alive = false;
		pthread_mutex_unlock(&philo->data->death_lock);
	}
	philo->state = new_state;
}

void	usleep_untill(struct timeval tval, \
struct timeval current_time, suseconds_t sleep_interval)
{
	suseconds_t	delta;

	delta = time_su_subtract(tval, current_time);
	sleep_interval = 50 * (sleep_interval > 100) + (sleep_interval > 0);
	(void)sleep_interval;
	while (delta >= 1)
	{
		gettimeofday(&current_time, NULL);
		delta = time_su_subtract(tval, current_time);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_t	*table_lock;
	int				*table;

	table_lock = &philo->data->table_lock;
	table = philo->data->table;
	pthread_mutex_lock(table_lock);
	table[philo->n - 1] = 1;
	table[philo->n % philo->data->n_philo] = 1;
	pthread_mutex_unlock(table_lock);
}
