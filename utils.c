/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:33 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/22 21:12:06 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alpha(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] != '+'))
			{
				printf("Error, please enter valid arguments\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	x;
	int		i;
	int		s;

	x = 0;
	s = 1;
	i = 0;
	while (str[i] == '\v' || str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		s = -s;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	return (s * x);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error, gettimeofday function failed\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t time)
{
	size_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(200);
	return (0);
}

int	print_error(int error)
{
	if (error == 1)
		printf("Error, please enter the right amount of arguments\n");
	else if (error == 2)
		printf("Error, philosophers shouldn't pass 200\n");
	else if (error == 3)
		printf("Error, meals count should be greater than 0\n");
	else if (error == 4)
		printf("Error, arguments should be greater than 0\n");
	return (0);
}
