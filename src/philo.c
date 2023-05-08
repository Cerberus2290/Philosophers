/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:19:26 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/05 13:14:42 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

typedef void	*(*t_routine)(void *);

int	create_threads(t_philo **ph)
{
	int	i;

	i = 0;
	(*ph)->data->st_time = gettime();
	(*ph)->data->death = 0;
	while (i < (*ph)->data->number)
	{
		if (pthread_create(&(*ph)[i].philo_thread, NULL, \
				(t_routine)philo_routine, &(*ph)[i]))
		{
			protect_datamutexes(ph);
			clear_philo(ph, -1, i, i);
			return (1);
		}
		if (pthread_mutex_init(&(*ph)[i].st_eating_mutex, NULL))
		{
			protect_datamutexes(ph);
			clear_philo(ph, -1, i, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(t_philo **ph, int philoid)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < philoid)
	{
		if (pthread_join((*ph)[i].philo_thread, NULL) != 0)
			error++;
		i++;
	}
	if (i == philoid)
		return (0);
	return (error);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	data->meals_eaten = 0;
	ph = malloc(data->number * sizeof(*ph));
	while (i < data->number && ph)
	{
		ph[i].philo_id = i + 1;
		ph[i].started_eating = 0;
		if (pthread_mutex_init(&ph[i].mutex_l_fork, NULL))
		{
			clear_philo(&ph, i, 0, 0);
			return (NULL);
		}
		if (i != data->number - 1)
			ph[i].mutex_r_fork = &ph[i + 1].mutex_l_fork;
		else
			ph[i].mutex_r_fork = &ph[0].mutex_l_fork;
		ph[i].data = data;
		i++;
	}
	return (ph);
}

void	protect_datamutexes(t_philo **ph)
{
	pthread_mutex_lock(&(*ph)->data->meals_mutex);
	(*ph)->data->meals_eaten = (*ph)->data->number;
	pthread_mutex_unlock(&(*ph)->data->meals_mutex);
	pthread_mutex_unlock(&(*ph)->data->data_mutex);
}
