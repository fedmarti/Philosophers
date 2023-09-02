/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:27:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 03:11:14 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include "time/ft_time.h"
#include <stdio.h>

static void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2", 2);
		n = 147483648;
	}
	else if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	n = n % 10;
	n = n + 48;
	write (fd, &n, 1);
}

//writes the time in milliseconds elapsed since start_time
// then if n is >= 0 prints n followed by a space
void	p_log_time(struct timeval start_time, struct timeval time, int n)
{
	int	timestamp;

	timestamp = (int)time_su_subtract(time, start_time);
	if (timestamp != 0)
		timestamp /= MILLISEC;
	ft_putnbr_fd(timestamp, 1);
	if (n < 0)
		return ;
	write(1, " ", 1);
	ft_putnbr_fd(n, 1);
	write(1, " ", 1);
}

// prints timestamp and announces state change
void	p_log_state_change(int philo_n, enum e_philo_state new_state, \
struct timeval start_time, struct timeval time)
{
	int	timestamp;

	timestamp = (int)time_su_subtract(time, start_time);
	if (timestamp != 0)
		timestamp /= MILLISEC;
	// p_log_time(start_time, time, philo_n);
	if (new_state == Thinking)
		// write (1, "is thinking\n", 13);
		printf("%d %d is thinking\n", timestamp, philo_n);
	else if (new_state == Sleeping)
		// write (1, "is sleeping\n", 13);
		printf("%d %d is sleeping\n", timestamp, philo_n);
	else if (new_state == Eating)
		// write (1, "is eating\n", 11);
		printf("%d %d is eating\n", timestamp, philo_n);
	else if (new_state == Dead)
		// write (1, "died\n", 6);
		printf("%d %d died\n", timestamp, philo_n);
	else
		// write (1, "has taken a fork\n", 18);
		printf("%d %d has taken a fork\n", timestamp, philo_n);
}