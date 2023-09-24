/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:16:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/20 19:07:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

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
		sem_close(data->all_full);
	if (data->death)
		sem_close(data->death);
	if (data->forks)
		sem_close(data->forks);
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

	data = d;
	sem_wait(data->monitor_sem);
	while (data->full_philos < data->n_philo)
	{
		sem_post(data->monitor_sem);
		sem_wait(data->all_full);
		sem_wait(data->monitor_sem);
		data->full_philos++;
	}
	data->thread_terminated = true;
	sem_post(data->monitor_sem);
	sem_post(data->death);
	return (NULL);
}

t_data	data_init(int argc, char **argv);

void	program_exit(t_data *data, pthread_t *thread)
{
	sem_wait(data->death);
	kill_all(data);
	sem_wait(data->monitor_sem);
	if (!data->thread_terminated)
	{
		while (data->full_philos < data->n_philo)
		{
			data->full_philos++;
			sem_post(data->all_full);
		}
	}
	sem_post(data->monitor_sem);
	pthread_join(*thread, NULL);
	sem_close(data->monitor_sem);
	data_free(data);
}

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
	data.monitor_sem = sem_open(MONITOR_SEM, O_CREAT, 777, 1);
	if (!data.monitor_sem)
	{
		kill_all(&data);
		data_free(&data);
		return (1);
	}
	sem_unlink(MONITOR_SEM);
	pthread_create(&meal_monitor, NULL, monitor_routine, &data);
	program_exit(&data, &meal_monitor);
	return (0);
}
