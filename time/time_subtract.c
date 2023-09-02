/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_subtract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:42:21 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/01 22:34:57 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

struct timeval	timeval_subtract(struct timeval tv1, struct timeval tv2)
{
	struct timeval	val;

	val.tv_usec = tv1.tv_usec - tv2.tv_usec;
	val.tv_sec = tv1.tv_sec - tv2.tv_sec;
	return (time_recalibrate(val));
}

suseconds_t	time_su_subtract(struct timeval tv1, struct timeval tv2)
{
	struct timeval	val;

	val.tv_usec = tv1.tv_usec - tv2.tv_usec;
	val.tv_sec = tv1.tv_sec - tv2.tv_sec;
	return (timeval_to_usec(time_recalibrate(val)));
}