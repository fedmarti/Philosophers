/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval_to_usec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:05:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 20:52:37 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_structs.h"
#include "ft_time.h"
#include <limits.h>

suseconds_t	timeval_to_usec(struct timeval tv)
{
	long long	temp;

	temp = tv.tv_sec * ONE_SEC + tv.tv_usec;
	if (temp <= LONG_MAX && temp >= LONG_MIN)
		return ((suseconds_t)temp);
	if (temp > 0)
		return (LONG_MAX);
	return (LONG_MIN);
}

struct timeval	usec_to_timeval(suseconds_t val)
{
	return (time_recalibrate((struct timeval){0, val}));
}
