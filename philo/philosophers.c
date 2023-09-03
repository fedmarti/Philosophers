/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:16:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/03 02:12:49 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
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
	if (!data->all_alive)
		pthread_mutex_destroy(&data->death_lock);
	data->n_philo = 0;
}

t_data	data_init(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!is_input_valid(argc, argv))
		return (1);
	data = data_init(argc, argv);
	if (data.n_philo == 0)
		return (1);
	start_philos(&data);
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(data.philosophers[i].thread, NULL);
		i++;
	}
	data_free(&data);
}
