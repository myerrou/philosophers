/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:29:33 by myerrou           #+#    #+#             */
/*   Updated: 2024/12/17 10:29:34 by myerrou          ###   ########.fr       */
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
				printf("error, you have to enter the right arguments\n");
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
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
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

void	print_error(int i)
{
	if (i == 0)
		printf("error, the arguments should be greater than 0 \n");
	else if (i == 1)
		printf("error,number of philosophers should be less than 200\n");
	else if (i == 2)
		printf("pthread failed\n");
	exit(1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday()failed\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t time)
{
	size_t	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time)
		usleep(500);
	return (0);
}
