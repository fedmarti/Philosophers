/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:28:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/01 22:34:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

struct timeval	timeval_add(struct timeval tv1, struct timeval tv2)
{
	struct timeval	val;

	val.tv_usec = tv1.tv_usec + tv2.tv_usec;
	val.tv_sec = tv1.tv_sec + tv2.tv_sec;
	return (time_recalibrate(val));
}

struct timeval	timeval_add_su(struct timeval timeval, suseconds_t amount)
{
	timeval.tv_usec += amount;
	return (time_recalibrate(timeval));
}
