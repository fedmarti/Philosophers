/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:47:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 23:26:51 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

void	think_state(t_philo *philo);
void	eat_state(t_philo *philo);
void	sleep_state(t_philo *philo);
void	data_free(t_data *data);

bool	death_check(t_philo *philo, struct timeval time)
{
	struct timeval	starvation_time;

	starvation_time = \
	timeval_add_su(philo->last_meal, philo->data->time_to_die * MILLISEC);
	if (time_su_subtract(starvation_time, time) <= 0)
		return (true);
	return (false);
}

#include <stdio.h>

void	*death_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	bool			alive;

	philo = arg;
	alive = true;
	while (alive)
	{
		sem_wait(philo->meal_time);
		gettimeofday(&time, NULL);
		alive = !death_check(philo, time);
		sem_post(philo->meal_time);
	}
	sem_post(philo->data->death);
	p_log_state_change(philo->n, Dead, philo->data->start_time, time);
	return (NULL);
}

char	*get_semaphore_name(int philo_n)
{
	char	*str;
	int		i;

	i = 3;
	str = malloc(sizeof(char) * SEM_NAME_LEN);
	if (!str)
		return (NULL);
	str[0] = philo_n / 100 % 10 + 48;
	str[1] = philo_n / 10 % 10 + 48;
	str[2] = philo_n % 10 + 48;
	while (i < SEM_NAME_LEN - 1)
	{
		str[i] = SEM_NAME[i - 3];
		i++;
	}
	str[i] = 0;
	return (str);
}

bool	philo_startup(t_philo *philo, pthread_t *monitor)
{
	int		philo_n;
	char	*sem_name;

	philo_n = philo->n;
	while (!philo->meal_time && philo_n < 800)
	{
		sem_name = get_semaphore_name(philo_n);
		if (!sem_name)
			return (false);
		philo->meal_time = sem_open(sem_name, O_CREAT, 777, 1);
		if (philo->meal_time == SEM_FAILED && errno == EACCES)
		{
			free(sem_name);
			philo_n += 200;
		}
	}
	if (!philo->meal_time)
		return (false);
	sem_unlink(sem_name);
	free(sem_name);
	pthread_create(monitor, NULL, death_routine, philo);
	return (true);
}

#include <stdio.h>

void	philo_logic(void *arg)
{
	t_philo		*philosopher;
	pthread_t	death_monitor;

	philosopher = arg;
	if (!philo_startup(philosopher, &death_monitor))
		sem_post(philosopher->data->death);
	usleep(200 * (philosopher->n > philosopher->data->n_philo / 2));
	while (philosopher->state != Dead)
	{
		if (philosopher->state == Eating)
			eat_state(philosopher);
		else if (philosopher->state == Thinking)
			think_state(philosopher);
		else if (philosopher->state == Sleeping)
			sleep_state(philosopher);
	}
	pthread_detach(death_monitor);
	data_free(philosopher->data);
	exit(0);
}
