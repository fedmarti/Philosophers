/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:29:14 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/24 23:05:59 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include "time/ft_time.h"
# include <semaphore.h>
# define DEATH_SEM "death"
# define FORKS_SEM "forks"
# define FULL_SEM "fullnes"
# define SEM_NAME "philo_sem"
# define SEM_NAME_LEN 13
# define MONITOR_SEM "philo_monitor_sem"

enum e_philo_state {
	Thinking,
	Eating,
	Sleeping,
	Dead,
	Taking_fork = -1,
	Taking_forks = -2,
	Putting_fork_down = -3
};

typedef struct s_philo {
	int					n;
	int					meal_count;
	struct timeval		last_meal;
	enum e_philo_state	state;
	struct s_data		*data;
	sem_t				*meal_time;
}	t_philo;

typedef struct s_data {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	pid_t			*philo_pid;
	t_philo			*philosophers;
	struct timeval	start_time;
	volatile bool	thread_terminated;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*all_full;
	sem_t			*monitor_sem;
	int				full_philos;
}	t_data;

int		is_input_valid(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	start_philos(t_data *data);
void	philo_logic(void *arg);
void	p_log_state_change(int philo_n, enum e_philo_state new_state, \
		struct timeval start_time, struct timeval time);
void	change_state(t_philo *philo, enum e_philo_state new_state, \
struct timeval time);
void	usleep_untill(struct timeval tval, struct timeval current_time);
void	put_down_forks(t_philo *philo);
bool	pick_up_fork(t_data *data, int fork_n);
bool	put_down_fork(t_data *data, int fork_n);

#endif