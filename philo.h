/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:29:14 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 03:06:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

enum e_philo_state {
	Thinking,
	Eating,
	Sleeping,
	Dead,
	Taking_forks = -1
};

typedef struct s_philo {
	pthread_t			thread;
	int					n;
	int					meal_count;
	struct timeval		last_meal;
	enum e_philo_state	state;
	struct s_data		*data;
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
	struct timeval	start_time;
}	t_data;

int		is_input_valid(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	start_philos(t_data *data);
void	*philo_logic(void *arg);
void	p_log_state_change(int philo_n, enum e_philo_state new_state, \
		struct timeval start_time, struct timeval time);
void	p_log_time(struct timeval start_time, struct timeval time, int n);

#endif