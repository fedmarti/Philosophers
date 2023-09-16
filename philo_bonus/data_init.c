/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:11:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/16 22:13:46 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <fcntl.h>

void	data_free(t_data *data);

static int	philo_alloc(t_data *data)
{
	data->philosophers = \
	ft_calloc(data->n_philo, sizeof(*(data->philosophers)));
	if (!data->philosophers)
	{
		data_free(data);
		return (0);
	}
	return (1);
}

static bool	semaphores_init(t_data *data)
{
	data->forks = sem_open(FORKS_SEM, O_CREAT, 777, data->n_philo);
	if (!data->forks)
	{
		data_free(data);
		return (false);
	}
	sem_unlink(FORKS_SEM);
	data->death = sem_open(DEATH_SEM, O_CREAT, 777, 0);
	if (!data->death)
	{
		data_free(data);
		return (false);
	}
	sem_unlink(DEATH_SEM);
	data->all_full = sem_open(FULL_SEM, O_CREAT, 777, 0);
	if (!data->all_full)
	{
		data_free(data);
		return (false);
	}
	sem_unlink(FULL_SEM);
	return (true);
}

t_data	data_init(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	data.n_philo = ft_atoi(argv[1]);
	if (data.n_philo <= 0)
		return (data);
	if (!philo_alloc(&data))
		return (data);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.philo_pid = ft_calloc(data.n_philo, sizeof(*data.philo_pid));
	if (!data.philo_pid)
	{
		data_free(&data);
		return (data);
	}
	if (!semaphores_init(&data))
		return (data);
	if (argc == 6)
		data.times_philo_must_eat = ft_atoi(argv[5]);
	else
		data.times_philo_must_eat = __INT_MAX__;
	return (data);
}
