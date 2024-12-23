/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:28 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/22 21:06:49 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DIE "has died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

typedef struct s_data
{
	int				nb_philos;
	int				meals_count;
	int				end_simulation;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			someone_died;
	pthread_t		monitor;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_mutex_t	execute;
	pthread_mutex_t	forks[200];
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eating;
	int				nb_eaten;
	size_t			last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}					t_philo;

// parse_init functions
int					parse_args(int ac, char **av, t_data *data);
void				init_data(t_philo *philo, t_data *data);
void				init_locks(t_data *data);
// philo2 functions
void				message(char *str, t_philo *philo);
void				do_sleeping(t_philo *philo);
void				do_thinking(t_philo *philo);
void				do_eating(t_philo *philo);
int					dead(t_philo *philo);
// philo1 functions
void				monitor_routine(void *arg);
void				*philo_routine(void *arg);
void				destruction(t_data *data);
// main functions
int					philo_died(t_philo *philo);
int					all_ate(t_philo *philo);
// utils functions
int					ft_atoi(const char *str);
int					ft_usleep(size_t time);
int					print_error(int error);
int					is_alpha(char **av);
size_t				get_time(void);

#endif
