/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:16:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/30 23:17:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	forks_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
}

void	data_free(t_data *data)
{
	pthread_mutex_destroy(&data->table_lock);
	if (data->table)
	{
		free(data->table);
		data->table = NULL;
	}
	if (data->fork_lock)
	{
		forks_destroy(data);
		free(data->fork_lock);
		data->fork_lock = NULL;
	}
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	data->n_philo = 0;
}

int	forks_init(t_data *data)
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

int	table_init(t_data *data)
{
	int i;
	
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

int	philo_init(t_data *data)
{
	// int	i;

	data->philosophers = \
	ft_calloc(data->n_philo, sizeof(*(data->philosophers)));
	if (!data->philosophers)
	{
		data_free(data);
		return (0);
	}
	// i = 0;
	// while (i < data->n_philo)
	// 	data->philosophers[i].n = ++i;
	return (1);
}

static t_data	data_init(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0,0,0,0,0,0,0,0};
	if (data.n_philo <= 0)
		return (data);
	data.n_philo = ft_atoi(argv[1]);
	if (!forks_init(&data))
		return (data);
	if (!table_init(&data))
		return (data);
	if (!philo_init(&data))
		return (data);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data.times_philo_must_eat = ft_atoi(argv[5]);
	else
		data.times_philo_must_eat = __INT_MAX__;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	if (!is_input_valid(argc, argv))
		return (1);
	data = data_init(argc, argv);
	if (data.n_philo == 0)
		return (1);
	//start all threads
	//put each thread into philo[n_thread].thread
	//code philo logic
	//	philo locks table mutex
	//	if philo can take two forks he takes them
	//		//locks both forks
	//	//unlocks table
	//		//eats
	//		//unlocks fork
	//		//eepy
	
}