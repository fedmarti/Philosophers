/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:41:46 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/25 18:45:51 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat_state(t_philo *philo)
{
	struct timeval		time;
	struct timeval		new_time;
	suseconds_t			usleep_time;

	usleep_time = philo->data->time_to_eat * MILLISEC;
	gettimeofday(&time, NULL);
	new_time = timeval_add_su(philo->last_meal, usleep_time);
	usleep_untill(new_time, time);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	new_time = return_time_of_day();
	change_state(philo, Sleeping, new_time);
}

	// p_log_state_change(philo->n, Putting_fork_down, 
	// philo->data->start_time, return_time_of_day());