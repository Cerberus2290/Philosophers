/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:09:36 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/18 17:16:23 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    *one_philo(void *p)
{
    t_philo *ph;

    ph = (t_philo *)p;
    pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
    philo_print(ph, "took a fork");
    ph->t_lastmeal = timestamp(ph->args);
    ft_sleep(ph, ph->args->t_to_die);
    philo_print(ph, "has died \xF0\x9F\x92\x80");
    ph->args->game_over = TRUE;
    return (NULL);
}