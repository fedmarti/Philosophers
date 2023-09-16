/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_recalibrate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:02:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:28:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_structs.h"

struct timeval	time_recalibrate(struct timeval tv)
{
	while (tv.tv_sec > 0 && tv.tv_usec < 0)
	{
		tv.tv_usec += ONE_SEC;
		tv.tv_sec--;
	}
	while (tv.tv_usec >= ONE_SEC)
	{
		tv.tv_usec -= ONE_SEC;
		tv.tv_sec++;
	}
	while (tv.tv_usec <= -ONE_SEC)
	{
		tv.tv_usec -= ONE_SEC;
		tv.tv_sec++;
	}
	while (tv.tv_sec < 0 && tv.tv_usec > 0)
	{
		tv.tv_usec -= ONE_SEC;
		tv.tv_sec++;
	}
	return (tv);
}
