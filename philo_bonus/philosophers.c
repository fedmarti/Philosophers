/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:16:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/16 22:15:39 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void	data_free(t_data *data)
{
	if (data->philo_pid)
	{
		free(data->philo_pid);
		data->philo_pid = NULL;
	}
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	if (data->all_full)
		sem_unlink(FULL_SEM);
	if (data->death)
		sem_unlink(DEATH_SEM);
	if (data->forks)
		sem_unlink(FORKS_SEM);
	data->n_philo = 0;
}

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		kill(data->philo_pid[i], SIGKILL);
		i++;
	}
}

void	*monitor_routine(void *d)
{
	t_data	*data;
	int		i;

	data = d;
	i = data->n_philo;
	while (i)
	{
		sem_wait(data->all_full);
		i--;
	}
	data->thread_terminated = true;
	sem_post(data->death);
	return (NULL);
}

t_data	data_init(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	meal_monitor;

	if (!is_input_valid(argc, argv))
		return (1);
	data = data_init(argc, argv);
	if (data.n_philo == 0)
		return (1);
	start_philos(&data);
	if (!data.n_philo)
		return (1);
	pthread_create(&meal_monitor, NULL, monitor_routine, &data);
	sem_wait(data.death);
	if (!data.thread_terminated)
		pthread_detach(meal_monitor);
	else
		pthread_join(meal_monitor, NULL);
	kill_all(&data);
	data_free(&data);
	return (0);
}
