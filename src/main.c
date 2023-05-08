/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:52:47 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/08 14:55:46 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*ph;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Syntax error. Use: ./philo [number_of_philos] [time_to_die] [time_to_eat] \
[time_to_sleep] (OPTIONAL - [number_time_must_eat])\n", 2);
		return (1);
	}
	data = init_struct(argv);
	if (!data.meals || !data.number || init_mutexes(&data))
		return (1);
	ph = init_philo(&data);
	if (!ph || pthread_mutex_lock(&data.data_mutex) || \
			create_threads(&ph))
		return (1);
	pthread_mutex_unlock(&data.data_mutex);
	if (handle_death(&data, &ph))
	{
		clear_philo(&ph, -1, data.number, data.number);
		clear_data(&data);
		return (3);
	}
	clear_philo(&ph, -1, data.number, data.number);
	clear_data(&data);
	return (0);
}
