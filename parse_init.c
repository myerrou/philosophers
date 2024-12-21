/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:12 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:16 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char **av, t_data *data)
{
	if (is_alpha(av) == 0)
	{
		data->nb_philos = ft_atoi(av[1]);
		if (data->nb_philos > 200)
			print_error(2);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			data->meals_count = ft_atoi(av[5]);
			if (data->meals_count == 0)
				print_error(3);
		}
		else
			data->meals_count = -1;
		if (data->time_to_die <= 0 || data->time_to_eat <= 0
			|| data->time_to_sleep <= 0 || data->nb_philos <= 0)
			print_error(4);
		return (1);
	}
	return (0);
}

void	init_data(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].nb_eaten = 0;
		philo[i].eating = 0;
		philo[i].last_meal = get_time();
		philo[i].fork_left = &data->forks[i];
		if (i == data->nb_philos - 1)
			philo[i].fork_right = &data->forks[0];
		else
			philo[i].fork_right = &data->forks[i + 1];
		philo[i].data = data;
		i++;
	}
}

void	init_locks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->start_time = get_time();
	data->end_simulation = 0;
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->execute, NULL);
}
