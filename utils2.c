/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:37 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/17 10:29:38 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		message("%zu %d " FORK "\n", philo);
		pthread_mutex_lock(philo->fork_left);
		message("%zu %d " FORK "\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		message("%zu %d " FORK "\n", philo);
		pthread_mutex_lock(philo->fork_right);
		message("%zu %d " FORK "\n", philo);
	}
	message("%zu %d " EAT "\n", philo);
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_current_time();
	philo->nb_eaten++;
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

void	message(char *str, t_philo *philo)
{
	if (dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->write);
	printf(str, get_current_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	do_sleeping(t_philo *philo)
{
	message("%zu %d " SLEEP "\n", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	do_thinking(t_philo *philo)
{
	message("%zu %d " THINK "\n", philo);
}
