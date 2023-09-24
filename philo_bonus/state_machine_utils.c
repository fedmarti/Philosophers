/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:26:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 23:25:28 by fedmarti         ###   ########.fr       */
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
		sem_wait(philo->meal_time);
		philo->last_meal = time;
		philo->meal_count++;
		sem_post(philo->meal_time);
		if (philo->meal_count == philo->data->times_philo_must_eat)
		{
			sem_post(philo->data->all_full);
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
			new_state = Dead;
		}
	}
	else if (new_state == Dead)
	{
		sem_post(philo->data->death);
	}
	philo->state = new_state;
}

void	usleep_untill(struct timeval tval, struct timeval current_time)
{
	suseconds_t	delta;

	delta = time_su_subtract(tval, current_time);
	usleep(delta - 70);
}

	// while (delta >= 5)
	// {
	// 	gettimeofday(&current_time, NULL);
	// 	delta = time_su_subtract(tval, current_time);
	// }