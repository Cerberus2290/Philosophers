/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:04:27 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:07 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_print(t_philo **ph, char *str)
{
	pthread_mutex_lock(&(*ph)->data->print_mutex);
	if (!check_meals_eaten(ph) && !check_death(ph))
	{
		printf(str, gettime() - (*ph)->data->st_time, (*ph)->philo_id);
	}
	pthread_mutex_unlock(&(*ph)->data->print_mutex);
}

void	philo_sleep(t_philo **ph, int nb)
{
	if (nb == 2)
	{
		philo_print(ph, "%lld %d is sleeping\n");
		sleep_function(ph, (*ph)->data->t_to_sleep);
	}
}
