/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:28:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 18:25:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include <limits.h>

struct timeval	timeval_add(struct timeval tv1, struct timeval tv2)
{
	struct timeval	val;
	long long		temp_usec;
	long long		temp_sec;

	temp_usec = (long long)tv1.tv_usec + (long long)tv2.tv_usec;
	temp_sec = 0;
	if (temp_usec <= LONG_MAX && temp_usec >= LONG_MIN)
		val.tv_usec = temp_usec;
	else
	{
		temp_sec = temp_usec / ONE_SEC;
		val.tv_usec = temp_usec % ONE_SEC;
	}
	temp_sec += (long long)tv1.tv_sec + (long long)tv2.tv_sec;
	if (temp_sec > LONG_MAX)
		val.tv_sec = LONG_MAX;
	else if (temp_sec < LONG_MIN)
		val.tv_sec = LONG_MIN;
	else
		val.tv_sec = temp_sec;
	return (time_recalibrate(val));
}

struct timeval	timeval_add_su(struct timeval timeval, suseconds_t amount)
{
	return (timeval_add(timeval, usec_to_timeval(amount)));
}
