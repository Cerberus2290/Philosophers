/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:05:56 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/05 13:23:12 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_meals_eaten(t_philo **ph)
{
	pthread_mutex_lock(&(*ph)->data->meals_mutex);
	if ((*ph)->data->meals_eaten == (*ph)->data->number)
	{
		pthread_mutex_unlock(&(*ph)->data->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*ph)->data->meals_mutex);
	return (0);
}

int	check_eating_time(t_philo **ph, int i, int id)
{
	if (i == 0)
	{
		pthread_mutex_lock(&(*ph)->st_eating_mutex);
		(*ph)->started_eating = (gettime() - (*ph)->data->st_time);
		pthread_mutex_unlock(&(*ph)->st_eating_mutex);
	}
	if (i == 1)
	{
		pthread_mutex_lock(&(*ph)[id].st_eating_mutex);
		if ((gettime() - (*ph)->data->st_time)
			- (*ph)[id].started_eating >= (*ph)->data->t_to_die)
		{
			pthread_mutex_unlock(&(*ph)[id].st_eating_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*ph)[id].st_eating_mutex);
	}
	return (0);
}

void	add_meals_eaten(t_philo **ph)
{
	pthread_mutex_lock(&(*ph)->data->meals_mutex);
	(*ph)->data->meals_eaten++;
	pthread_mutex_unlock(&(*ph)->data->meals_mutex);
}

int	take_l_fork(t_philo **ph)
{
	int	lfork;

	lfork = 0;
	if (!check_death(ph) && !check_meals_eaten(ph))
	{
		pthread_mutex_lock(&(*ph)->mutex_l_fork);
		lfork += 1;
		if ((*ph)->data->number != 1)
		{
			pthread_mutex_lock((*ph)->mutex_r_fork);
			lfork += 1;
		}
		philo_print(ph, "%lld %d has taken a fork\n");
	}
	return (lfork);
}

void	philo_eat(t_philo **ph, int fork)
{
	if (fork == 2)
	{
		check_eating_time(ph, 0, 0);
		philo_print(ph, "%lld %d has taken a fork\n");
		philo_print(ph, "%lld %d is eating\n");
		sleep_function(ph, (*ph)->data->t_to_eat);
		pthread_mutex_unlock(&(*ph)->mutex_l_fork);
	}
}
