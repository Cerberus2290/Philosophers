/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:51:30 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/08 14:57:51 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clear_data(t_data *data)
{
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
}

void	clear_philo(t_philo **ph, int forknbr, int eatnbr, int philonbr)
{
	int	i;

	i = 0;
	if (forknbr == -1)
		forknbr = (*ph)->data->number;
	join_threads(ph, philonbr);
	i = 0;
	while (i < eatnbr)
	{
		pthread_mutex_destroy(&(*ph)[i].st_eating_mutex);
		i++;
	}
	i = 0;
	while (i < forknbr)
	{
		pthread_mutex_destroy(&(*ph)[i].mutex_l_fork);
		i++;
	}
	free(*ph);
}

int	*parse_and_check(char **argv, int *args)
{
	int	i;

	i = 0;
	while (argv[i + 1])
	{
		args[i] = ft_atoi(argv[i + 1]);
		if (args[i] == -1 || args[i] != ft_atol(argv[i + 1]))
			return (NULL);
		i++;
	}
	if (args[0] == 0 || args[0] >= 201)
		return (NULL);
	if (argv[5] == NULL)
		args[4] = -1;
	return (args);
}
