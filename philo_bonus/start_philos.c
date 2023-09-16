/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:31:54 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/16 20:21:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/types.h>
#include <unistd.h>

void	kill_all(t_data *data);
void	data_free(t_data *data);

void	start_philos(t_data *data)
{
	int		i;
	pid_t	pid;
	t_philo	*current;

	i = 0;
	gettimeofday(&data->start_time, NULL);
	while (i < data->n_philo)
	{
		current = &data->philosophers[i];
		current->state = Thinking;
		current->data = data;
		current->n = i + 1;
		current->last_meal = data->start_time;
		pid = fork();
		if (!pid)
			philo_logic(current);
		else if (pid == -1)
		{
			data->n_philo = i--;
			kill_all(data);
			return (data_free(data));
		}
		data->philo_pid[i] = pid;
		i++;
	}
}
