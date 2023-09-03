/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:11:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:20:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	data_free(t_data *data);

static int	forks_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork_lock = ft_calloc(data->n_philo, sizeof(*(data->fork_lock)));
	if (!data->fork_lock)
		return (0);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	return (1);
}

static int	table_init(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->table_lock, NULL);
	data->table = ft_calloc(data->n_philo, sizeof(*(data->table)));
	if (!data->table)
	{
		data_free(data);
		return (0);
	}
	i = 0;
	while (i < data->n_philo)
	{
		data->table[i] = 1;
		i++;
	}
	return (1);
}

int	philo_alloc(t_data *data)
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

t_data	data_init(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	data.n_philo = ft_atoi(argv[1]);
	if (data.n_philo <= 0)
		return (data);
	if (!forks_init(&data))
		return (data);
	if (!table_init(&data))
		return (data);
	if (!philo_alloc(&data))
		return (data);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.all_alive = true;
	pthread_mutex_init(&data.death_lock, NULL);
	if (argc == 6)
		data.times_philo_must_eat = ft_atoi(argv[5]);
	else
		data.times_philo_must_eat = __INT_MAX__;
	return (data);
}
