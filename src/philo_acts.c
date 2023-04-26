/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:09:36 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/26 14:30:54 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* simulates the behavior of one philosopher */
void	*one_philo(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
	philo_print(ph, "has taken a fork \xF0\x9F\x8D\xB4");
	pthread_mutex_lock(&ph->args->game_over_mutex);
	ph->t_lastmeal = timestamp(ph->args);
	pthread_mutex_unlock(&ph->args->game_over_mutex);
	ft_sleep(ph, ph->args->t_to_die);
	philo_print(ph, "died \xF0\x9F\x92\x80");
	ph->args->game_over = TRUE;
	return (NULL);
}

/* checks if a philosopher is able to eat
also checks flag 'game_over' to see if philosopher is dead */
void	philo_eats(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
		philo_print(ph, "has taken a fork \xF0\x9F\x8D\xB4");
		pthread_mutex_lock(&ph->args->fork[ph->r_fork]);
		philo_print(ph, "has taken a fork \xF0\x9F\x8D\xB4");
		philo_print(ph, "is eating \xF0\x9F\x8D\x9D");
		ph->t_lastmeal = timestamp(ph->args);
		pthread_mutex_lock(&ph->lastmeal_mutex);
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->lastmeal_mutex);
		ft_sleep(ph, ph->args->t_to_eat);
		pthread_mutex_unlock(&ph->args->fork[ph->l_fork]);
		pthread_mutex_unlock(&ph->args->fork[ph->r_fork]);
	}
}

/* prints message for philosopher thinking
if not dead */
void	philo_thinks(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
		philo_print(ph, "is thinking \xF0\x9F\x92\xAD");
}

/* prints message for philosopher sleeping
if not dead */
void	philo_sleeps(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		philo_print(ph, "is sleeping \xF0\x9F\x98\xB4");
		ft_sleep(ph, ph->args->t_to_sleep);
	}
}
