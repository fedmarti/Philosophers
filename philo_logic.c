/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:47:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 03:19:17 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include "time/ft_time.h"
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

void	change_state(t_philo *philo, enum e_philo_state new_state, \
struct timeval time)
{
	p_log_state_change(philo->n, new_state, philo->data->start_time, time);
	if (new_state == Eating)
	{
		philo->last_meal = time;
		philo->meal_count++;
	}
	philo->state = new_state;
}

void	usleep_untill(struct timeval tval, struct timeval current_time)
{
	suseconds_t	delta;

	delta = time_su_subtract(tval, current_time);
	if (delta <= 0)
		return ;
	usleep(delta - 100);
}

void	sleep_state(t_philo *philo)
{
	struct timeval		time;
	struct timeval		new_time;
	suseconds_t			usleep_time;
	enum e_philo_state	new_state;

	gettimeofday(&time, NULL);
	if (philo->data->time_to_eat + philo->data->time_to_sleep \
	> philo->data->time_to_die)
	{
		usleep_time = philo->data->time_to_die * MILLISEC;
		new_state = Dead;
	}
	else
	{
		usleep_time = \
		(philo->data->time_to_sleep + philo->data->time_to_eat) * MILLISEC;
		new_state = Thinking;
	}
	new_time = timeval_add_su(philo->last_meal, usleep_time);
	usleep_untill(new_time, time);
	change_state(philo, new_state, new_time);
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
	pthread_mutex_unlock(&philo->data->fork_lock[philo->n - 1]);
	pthread_mutex_unlock(&philo->data->fork_lock[philo->n \
	% philo->data->n_philo]);
}

void	eat_state(t_philo *philo)
{
	struct timeval		time;
	struct timeval		new_time;
	suseconds_t			usleep_time;
	enum e_philo_state	new_state;

	gettimeofday(&time, NULL);
	if (philo->data->time_to_eat > philo->data->time_to_die)
	{
		usleep_time = philo->data->time_to_die * MILLISEC;
		new_state = Dead;
	}
	else
	{
		usleep_time = philo->data->time_to_eat * MILLISEC;
		new_state = Sleeping;
	}
	new_time = timeval_add_su(philo->last_meal, usleep_time);
	usleep_untill(new_time, time);
	put_down_forks(philo);
	change_state(philo, new_state, new_time);
}

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

void	think_state(t_philo *philo)
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
		taken_both_forks = true;
		p_log_state_change(philo->n, Taking_forks, philo->data->start_time, time);
		p_log_state_change(philo->n, Taking_forks, philo->data->start_time, time);
	}
	pthread_mutex_unlock(table_lock);
	if (!taken_both_forks)
		return ;
	pthread_mutex_lock(&philo->data->fork_lock[philo->n - 1]);
	pthread_mutex_lock(&philo->data->fork_lock[philo->n \
	% philo->data->n_philo]);
	change_state(philo, Eating, time);
}

void	*philo_logic(void *arg)
{
	t_philo	*philosopher;

	philosopher = arg;
	while (philosopher->state != Dead \
	&& philosopher->meal_count < philosopher->data->times_philo_must_eat)
	{
		if (philosopher->state == Eating)
			eat_state(philosopher);
		else if (philosopher->state == Thinking)
			think_state(philosopher);
		else if (philosopher->state == Sleeping)
			sleep_state(philosopher);
	}
	return (NULL);
}
