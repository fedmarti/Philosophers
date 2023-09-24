/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:27:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/20 20:12:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <unistd.h>
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE

void	think_state(t_philo *philo)
{
	struct timeval	time;

	sem_wait(philo->data->forks);
	gettimeofday(&time, NULL);
	p_log_state_change(philo->n, Taking_fork, philo->data->start_time, time);
	sem_wait(philo->data->forks);
	gettimeofday(&time, NULL);
	p_log_state_change(philo->n, Taking_fork, philo->data->start_time, time);
	change_state(philo, Eating, time);
}
