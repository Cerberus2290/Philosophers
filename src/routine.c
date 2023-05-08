/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:35:49 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/05 13:15:06 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(t_philo *ph)
{
	int	i;
	int	fork;

	i = 0;
	pthread_mutex_lock(&ph->data->data_mutex);
	pthread_mutex_unlock(&ph->data->data_mutex);
	if (ph->philo_id % 2 == 0)
		sleep_function(&ph, 1);
	while (!check_meals_eaten(&ph) && ph->data->meals != 0
		&& !check_death(&ph))
	{
		if (ph->data->number != 1)
			philo_print(&ph, "%lld %d is thinking\n");
		fork = take_l_fork(&ph);
		philo_eat(&ph, fork);
		if (fork > 0)
			pthread_mutex_unlock((ph)->mutex_r_fork);
		if (ph->data->meals > 0 && (i + 1) == ph->data->meals && fork == 2)
			add_meals_eaten(&ph);
		philo_sleep(&ph, fork);
		i++;
		while (!check_death(&ph) && (ph->data->number == 1 && i))
			usleep(150);
	}
	return (ph);
}

void	sleep_function(t_philo **ph, long long msec)
{
	long long	timestamp;

	timestamp = gettime();
	while (!check_death(ph) && !check_meals_eaten(ph)
		&& gettime() - timestamp < msec)
		usleep(150);
}

long long	gettime(void)
{
	t_timeval		now;
	unsigned long	time;

	if (gettimeofday(&now, NULL) != 0)
	{
		ft_putstr_fd("Error in gettime()\n", 2);
		return (-1);
	}
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	return (time);
}
