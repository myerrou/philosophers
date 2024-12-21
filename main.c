/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:02 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/21 14:40:41 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->meal);
		if (get_time() - philo[i].last_meal > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->dead);
			pthread_mutex_unlock(&philo->data->meal);
			philo->data->end_simulation = 1;
			pthread_mutex_lock(&philo->data->ring);
			pthread_mutex_unlock(&philo->data->dead);
			printf("%zu %d " DIE "\n", get_time() - philo->data->start_time,
				philo[i].id);
			pthread_mutex_unlock(&philo->data->ring);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->meal);
		i++;
	}
	return (0);
}

int	all_ate(t_philo *philo)
{
	int	i;
	int	eat_times;

	if (philo->data->meals_count == -1)
		return (0);
	i = 0;
	eat_times = 0;
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->meal);
		if (philo[i].nb_eaten >= philo->data->meals_count)
			eat_times++;
		pthread_mutex_unlock(&philo->data->meal);
		i++;
	}
	if (eat_times == philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->dead);
		philo->data->end_simulation = 1;
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philos[200];
	int		i;

	if (ac < 5 || ac > 6)
		print_error(1);
	if (parse_args(ac, av, &data))
	{
		init_locks(&data);
		init_data(philos, &data);
		i = 0;
		while (i < philos->data->nb_philos)
		{
			pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]);
			i++;
		}
		monitor_routine(philos);
		i = 0;
		while (i < philos->data->nb_philos)
			pthread_join(philos[i++].thread, NULL);
		destruction(&data);
	}
}
