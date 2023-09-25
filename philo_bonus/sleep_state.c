/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:25:15 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/25 20:28:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	sleep_state(t_philo *philo)
{
	struct timeval		time;
	struct timeval		new_time;
	suseconds_t			usleep_time;

	gettimeofday(&time, NULL);
	usleep_time = \
	(philo->data->time_to_sleep + philo->data->time_to_eat) * MILLISEC;
	new_time = timeval_add_su(philo->last_meal, usleep_time);
	usleep_untill(new_time, time);
	change_state(philo, Thinking, new_time);
	usleep(100);
}
