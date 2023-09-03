/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:37:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:09:48 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	left(int i, t_data *data)
{
	if (i < 0)
		return (data->n_philo - i);
	return (i);
}

int	right(int i, t_data *data)
{
	return (i % data->n_philo);
}

bool	check_fork_availability(int n, t_data *data)
{
	bool	available;

	pthread_mutex_lock(&data->fork_lock[n]);
	available = (data->table[n] != 0);
	pthread_mutex_unlock(&data->fork_lock[n]);
	return (available);
}
