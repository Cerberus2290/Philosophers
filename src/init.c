/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:09:44 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/30 20:53:46 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* checks if user input is according to subject*/
int	check_input(int argc, char **argv)
{
	int	i;
	int	res;

	if (argc != 5 && argc != 6)
	{
		printf("%s", ERR_CMD);
		return (-1);
	}
	i = 0;
	while (argv[++i])
	{
		res = ft_atoi(argv[i]);
		if (i == 1 && res >= 201)
		{
			printf(ERR_MAX);
			return (-1);
		}
		if (res <= 0)
		{
			printf(ERR_ARGS);
			return (-1);
		}
	}
	return (0);
}

/* sets up the program settings and state information*/
void	init_s_control(char **argv, t_control *input)
{
	int	i;

	i = -1;
	input->error = FALSE;
	input->game_over = FALSE;
	input->end_meal = 0;
	input->nb_philo = ft_atoi(argv[1]);
	input->t_to_die = ft_atoi(argv[2]);
	input->t_to_eat = ft_atoi(argv[3]);
	input->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input->max_meals = ft_atoi(argv[5]);
	else
		input->max_meals = FALSE;
	input->philo = ft_calloc(input->nb_philo, (sizeof(t_philo)));
	input->fork = ft_calloc(input->nb_philo, (sizeof(pthread_mutex_t)));
	input->mealseaten_mutex = ft_calloc(input->nb_philo, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&input->game_over_mutex, NULL);
	while (++i < input->nb_philo)
	{
		pthread_mutex_init(&input->fork[i], NULL);
		pthread_mutex_init(&input->mealseaten_mutex[i], NULL);
	}
	init_s_philo(input);
	input->t0 = start_time();
}

/* initializes the philo_struct with starting values
so the program starts consistently */
void	init_s_philo(t_control *input)
{
	int		i;

	i = 0;
	while (i < input->nb_philo)
	{
		input->philo[i].id = i + 1;
		input->philo[i].meals_eaten = 0;
		input->philo[i].t_lastmeal = 0;
		input->philo[i].l_fork = i;
		input->philo[i].r_fork = (i + 1) % input->nb_philo;
		input->philo[i].args = input;
		pthread_mutex_init(&(input->philo[i].lastmeal_mutex), NULL);
		i++;
	}
}
