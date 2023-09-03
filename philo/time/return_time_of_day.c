/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_time_of_day.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:38:03 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:17:46 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_structs.h"

struct timeval	return_time_of_day(void)
{
	struct timeval	time;

	gettimeofday(&time, (void *)0);
	return (time);
}
