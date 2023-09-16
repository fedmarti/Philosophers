/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:01:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:17:53 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include "time_structs.h"

struct timeval	time_recalibrate(struct timeval tv);
struct timeval	timeval_add(struct timeval tv1, struct timeval tv2);
struct timeval	timeval_add_su(struct timeval timeval, suseconds_t amount);
struct timeval	timeval_subtract(struct timeval tv1, struct timeval tv2);
suseconds_t		time_su_subtract(struct timeval tv1, struct timeval tv2);
suseconds_t		timeval_to_usec(struct timeval tv);
struct timeval	usec_to_timeval(suseconds_t val);
struct timeval	return_time_of_day(void);

#endif