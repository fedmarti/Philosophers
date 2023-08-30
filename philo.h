/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:29:14 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/30 22:30:05 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <time.h>
# include <stdbool.h>

typedef struct s_philo {
	// bool			alive;
	pthread_t		thread;
	int				n;
	int				meal_count;
	struct timeval	last_meal;
}	t_philo;

typedef struct s_data {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	pthread_mutex_t	table_lock;
	int				*table;
	pthread_mutex_t	*fork_lock;
	t_philo			*philosophers;
}	t_data;

int		is_input_valid(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif