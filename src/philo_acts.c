/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:09:36 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/20 14:36:06 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* simulates the behavior of one philosopher */
void	*one_philo(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
	philo_print(ph, "took a fork");
	ph->t_lastmeal = timestamp(ph->args);
	ft_sleep(ph, ph->args->t_to_die);
	philo_print(ph, "has died \xF0\x9F\x92\x80");
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
		philo_print(ph, "took a fork");
		pthread_mutex_lock(&ph->args->fork[ph->r_fork]);
		philo_print(ph, "took a fork");
		philo_print(ph, "eating spaghetti");
		ph->t_lastmeal = timestamp(ph->args);
		ph->meals_eaten++;
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
		philo_print(ph, "'s thinking");
}

/* prints message for philosopher sleeping
if not dead */
void	philo_sleeps(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		philo_print(ph, "'s sleeping");
		ft_sleep(ph, ph->args->t_to_sleep);
	}
}
