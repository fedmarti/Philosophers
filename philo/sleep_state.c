/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:25:15 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 18:54:48 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	usleep_untill(new_time, time, usleep_time);
	change_state(philo, new_state, new_time);
}
