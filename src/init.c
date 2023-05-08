/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:09:36 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/08 15:01:12 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	init_struct(char **argv)
{
	t_data	data;

	if (parse_and_check(argv, (int *)&data) == NULL)
	{
		ft_putstr_fd("Invalid args - ", 2);
		ft_putstr_fd("Number of Philos must be between 1 and 200 | \
other arguments must be positive int\n", 2);
		data.meals = 0;
	}
	return (data);
}

int	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->data_mutex, NULL);
	if (pthread_mutex_init(&data->death_mutex, NULL))
	{
		pthread_mutex_destroy(&data->data_mutex);
		return (1);
	}
	else if (pthread_mutex_init(&data->meals_mutex, NULL))
	{
		pthread_mutex_destroy(&data->data_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		return (1);
	}
	else if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		pthread_mutex_destroy(&data->data_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meals_mutex);
		return (1);
	}
	return (0);
}
