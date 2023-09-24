/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_recalibrate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:02:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 21:16:48 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_structs.h"
#include <stdio.h>

struct timeval	time_recalibrate(struct timeval tv)
{
	long	sign;

	if (tv.tv_usec == 0)
		return (tv);
	tv.tv_sec += tv.tv_usec / ONE_SEC;
	tv.tv_usec %= ONE_SEC;
	sign = (tv.tv_sec > 0) - (tv.tv_sec < 0);
	while ((long)(tv.tv_sec ^ tv.tv_usec) < 0 && tv.tv_sec != 0)
	{
		tv.tv_sec -= sign;
		tv.tv_usec += ONE_SEC * sign;
	}
	return (tv);
}
