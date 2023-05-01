/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:52:47 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/30 21:00:32 by tstrassb         ###   ########.fr       */
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
	int			reached_max_meals;

	reached_max_meals = 0;
	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(2000);
	while (input->game_over == FALSE)
	{
		pthread_mutex_lock(&input->mealseaten_mutex[ph->id - 1]);
		reached_max_meals = (input->max_meals > 0 && ph->meals_eaten == input->max_meals);
		pthread_mutex_unlock(&input->mealseaten_mutex[ph->id - 1]);
		if (reached_max_meals)
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
	long long	lastmeal;

	pthread_mutex_lock(&p->args->game_over_mutex);
	pthread_mutex_lock(&p->lastmeal_mutex);
	lastmeal = p->t_lastmeal;
	pthread_mutex_unlock(&p->lastmeal_mutex);
	if ((timestamp(p->args) - lastmeal) >= p->args->t_to_die
		&& !p->args->game_over)
	{
		philo_print(p, "died \xF0\x9F\x92\x80");
		p->args->game_over = TRUE;
	}
	pthread_mutex_unlock(&p->args->game_over_mutex);
}

/* cleans up resources of simulation
joins all philosopher threads & destroys mutexes
frees allocated memory */
void	philo_over(t_control *input)
{
	int	i;

	i = input->nb_philo;
	while (--i >= 0)
	{
		pthread_join(input->philo[i].tid, NULL);
		pthread_mutex_destroy(&input->philo[i].lastmeal_mutex);
		pthread_mutex_destroy(&input->mealseaten_mutex[i]);
	}
	while (++i < input->nb_philo)
		pthread_mutex_destroy(&input->fork[i]);
	pthread_mutex_destroy(&input->game_over_mutex);
	free(input->philo);
	free(input->fork);
	free(input->mealseaten_mutex);
	free(input);
}
