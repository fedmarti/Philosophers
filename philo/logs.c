/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:27:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 21:36:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include "time/ft_time.h"
#include <stdio.h>
#include <limits.h>

// prints timestamp and announces state change
void	p_log_state_change(t_philo *philo, enum e_philo_state new_state, \
struct timeval time)
{
	long			timestamp;
	struct timeval	start_time;

	pthread_mutex_lock(&philo->data->print_lock);
	start_time = philo->data->start_time;
	timestamp = time_su_subtract(time, start_time);
	if (timestamp != 0)
		timestamp /= MILLISEC;
	printf("%li %d ", timestamp, philo->n);
	if (new_state == Thinking)
		printf("is thinking\n");
	else if (new_state == Sleeping)
		printf("is sleeping\n");
	else if (new_state == Eating)
		printf("is eating\n");
	else if (new_state == Dead)
		printf("died\n");
	else if (new_state == Taking_fork)
		printf("has taken a fork\n");
	else if (new_state == Taking_forks)
		printf("has taken a fork\n%li %d has taken a fork\n", \
		timestamp, philo->n);
	else if (new_state == Putting_fork_down)
		printf("has put the fork down\n");
	pthread_mutex_unlock(&philo->data->print_lock);
}
