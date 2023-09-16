/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:27:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:17:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include "time/ft_time.h"
#include <stdio.h>

// prints timestamp and announces state change
void	p_log_state_change(int philo_n, enum e_philo_state new_state, \
struct timeval start_time, struct timeval time)
{
	int	timestamp;

	timestamp = (int)time_su_subtract(time, start_time);
	if (timestamp != 0)
		timestamp /= MILLISEC;
	if (new_state == Thinking)
		printf("%d %d is thinking\n", timestamp, philo_n);
	else if (new_state == Sleeping)
		printf("%d %d is sleeping\n", timestamp, philo_n);
	else if (new_state == Eating)
		printf("%d %d is eating\n", timestamp, philo_n);
	else if (new_state == Dead)
		printf("%d %d died\n", timestamp, philo_n);
	else if (new_state == Taking_fork)
		printf("%d %d has taken a fork\n", timestamp, philo_n);
	else if (new_state == Taking_forks)
		printf("%d %d has taken a fork\n%d %d has taken a fork\n", \
		timestamp, philo_n, timestamp, philo_n);
	else if (new_state == Putting_fork_down)
		printf("%d %d has put the fork down\n", timestamp, philo_n);
}
