/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:47:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/05 18:25:43 by fedmarti         ###   ########.fr       */
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

static void	lonely_philo(t_philo *sad)
{
	struct timeval	time;
	struct timeval	newtime;

	gettimeofday(&time, NULL);
	newtime = timeval_add_su(sad->last_meal, sad->data->time_to_die * MILLISEC);
	p_log_state_change(1, Taking_fork, sad->last_meal, time);
	usleep_untill(newtime, time, sad->data->time_to_die);
	change_state(sad, Dead, newtime);
}

void	*philo_logic(void *arg)
{
	t_philo	*philosopher;

	philosopher = arg;
	if (philosopher->data->n_philo == 1)
		lonely_philo(philosopher);
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
