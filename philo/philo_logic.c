/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:47:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:11:08 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_state(t_philo *philo);
void	eat_state(t_philo *philo);
void	sleep_state(t_philo *philo);

bool	check_all_alive(t_data *data)
{
	bool	all_alive;

	pthread_mutex_lock(&data->death_lock);
	all_alive = data->all_alive;
	pthread_mutex_unlock(&data->death_lock);
	return (all_alive);
}

void	*philo_logic(void *arg)
{
	t_philo	*philosopher;

	philosopher = arg;
	while (philosopher->state != Dead && check_all_alive(philosopher->data))
	{
		if (philosopher->state == Eating)
			eat_state(philosopher);
		else if (philosopher->state == Thinking)
			think_state(philosopher);
		else if (philosopher->state == Sleeping)
			sleep_state(philosopher);
	}
	return (NULL);
}
