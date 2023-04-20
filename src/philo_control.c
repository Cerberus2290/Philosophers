/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:52:47 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/20 15:43:15 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* creates a thread for each philosopher 
and loops until a philosopher has died */
void	philo_start(t_control *input)
{
	int	i;

	if (input->nb_philo == 1)
		one_philo(input->philo);
	else
	{
		i = -1;
		while (++i < input->nb_philo)
			pthread_create(&input->philo[i].tid, NULL, \
			&philo_act, (void *) &input->philo[i]);
		while (input->game_over == FALSE)
			checking(input);
	}
}

/* simulates the behavior of the philosophers
controls philosopher taking forks, eating, sleeping, thinking
ensures philosopher do not start eating all at once */
void	*philo_act(void *p)
{
	t_philo		*ph;
	t_control	*input;

	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(1500);
	while (input->game_over == FALSE)
	{
		if (input->max_meals > 0 && ph->meals_eaten == input->max_meals)
			break ;
		philo_eats(ph);
		philo_sleeps(ph);
		philo_thinks(ph);
	}
	return (NULL);
}

/* checks status of simulation
ensures simulation stops if:
-philospher died
-all philosophers have eaten max number of meals */
void	checking(t_control *c)
{
	int	meal_i;
	int	death_i;

	meal_i = 0;
	death_i = 0;
	while (c->game_over == FALSE)
	{
		check_death(&c->philo[death_i]);
		if (c->max_meals > 0)
		{
			while (meal_i < c->nb_philo)
			{
				if (c->philo[meal_i].meals_eaten < c->max_meals)
					break ;
				meal_i++;
			}
			if (meal_i == c->nb_philo)
				c->game_over = TRUE;
		}
		usleep(5000);
		if (death_i == c->nb_philo - 1)
			death_i = -1;
		death_i++;
	}
}

/* checks if a philosopher has died
prints a message that philosopher died
ensures that only one philosopher can check death at a time */
void	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->args->checker);
	if ((timestamp(p->args) - p->t_lastmeal) >= p->args->t_to_die)
	{
		philo_print(p, "has died");
		p->args->game_over = TRUE;
	}
	pthread_mutex_unlock(&p->args->checker);
}

void	philo_over(t_control *input)
{
	int	i;

	i = input->nb_philo;
	while (--i >= 0)
		pthread_join(input->philo[i].tid, NULL);
	
}