/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:19:26 by tstrassb          #+#    #+#             */
/*   Updated: 2023/03/23 13:34:56 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* simply calls on the time of day without any arguments */
long long	start_time(void)
{
	struct timeval	t0;

	gettimeofday(&t0, NULL);
	return ((t0.tv_sec * 1000) + (t0.tv_usec / 1000));
}

/* returns elapsed time referenced from time stored in struct t_control */
long long	timestamp(t_control *input)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec * 1000) + (current.tv_usec / 1000)) - input->t0);
}

/* utility function to make philosopher sleep */
void	ft_sleep(t_philo *p, int t_wait)
{
	long long	time_now;
	long long	time_diff;

	time_now = timestamp(p->args);
	while (1)
	{
		time_diff = (timestamp(p->args) - time_now);
		if (time_diff >= t_wait)
			break ;
		usleep(1000);
	}
}
