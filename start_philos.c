/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:31:54 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 02:43:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos(t_data *data)
{
	int		i;
	t_philo	*current;

	i = 0;
	gettimeofday(&data->start_time, NULL);
	while (i < data->n_philo)
	{
		current = &data->philosophers[i];
		current->state = Thinking;
		current->data = data;
		current->n = i + 1;
		current->last_meal = data->start_time,
		pthread_create(&data->philosophers[i].thread, NULL, philo_logic, current);
		i++;
	} 
}