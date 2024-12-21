/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:24 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:16 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destruction(t_data *sh_data)
{
	int	i;

	i = 0;
	while (i < sh_data->nb_philos)
	{
		pthread_mutex_destroy(&sh_data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sh_data->meal);
	pthread_mutex_destroy(&sh_data->dead);
	pthread_mutex_destroy(&sh_data->execute);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		message("%zu %d " FORK "\n", philo);
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead(philo))
	{
		do_eating(philo);
		do_sleeping(philo);
		do_thinking(philo);
		if (philo->data->nb_philos == 3)
			ft_usleep(1);
	}
	return (arg);
}

void	monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_died(philo) || all_ate(philo))
			break ;
	}
}
