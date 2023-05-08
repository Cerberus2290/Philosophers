/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:09:44 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/08 14:46:53 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_philo **ph)
{
	pthread_mutex_lock(&(*ph)->data->death_mutex);
	if ((*ph)->data->death == 1)
	{
		pthread_mutex_unlock(&(*ph)->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*ph)->data->death_mutex);
	return (0);
}

int	handle_death(t_data *data, t_philo **ph)
{
	int	i;

	while (!check_death(ph) && \
			!check_meals_eaten(ph) && data->meals != 0)
	{
		i = 0;
		while (i < data->number && !check_death(ph) && \
				!check_meals_eaten(ph))
		{
			if (check_eating_time(ph, 1, i))
			{
				pthread_mutex_lock(&(*ph)->data->print_mutex);
				printf("%lld %d died \xF0\x9F\x92\x80\n", gettime()
					- (*ph)->data->st_time, (*ph)[i].philo_id);
				pthread_mutex_unlock(&(*ph)->data->print_mutex);
				if (pthread_mutex_lock(&data->death_mutex))
					return (-1);
				data->death = 1;
				pthread_mutex_unlock(&data->death_mutex);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}
