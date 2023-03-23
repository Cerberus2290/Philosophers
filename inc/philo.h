/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:37:48 by tstrassb          #+#    #+#             */
/*   Updated: 2023/03/23 12:58:39 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define RED "\e[0;31m"
# define RESET "\e[0m"

# define FALSE	0
# define TRUE	1
# define ERR_CMD "ERR_CMD\n"
# define ERR_MAX "ERR_MAX\n"
# define ERR_ARGS "ERR_ARGS\n"

typedef struct s_control	t_control;
typedef struct s_philo		t_philo;

/* struct to store all info about philosophers */
typedef struct s_philo
{
	phthread_t	tid;
	int			id;
	int			meals_eaten;
	long long	t_lastmeal;
	int			l_fork;
	int			r_fork;
	t_control	*args;
}	t_philo;

/* struct to store info about eat, sleep, die */
typedef struct s_control
{
	int					nb_philo;
	long long			t0;
	long long			t_to_die;
	long long			t_to_eat;
	long long			t_to_sleep;
	int					max_meals;
	t_philo				*philo;
	phthread_mutex_t	*fork;
	phthread_mutex_t	cout;
	phthread_mutex_t	checker;
	int					error;
	int					end_meal;
	int					game_over;
}	t_control;

/* functions of init.c */

/* functions of timeutils.c */

/* functions of utils.c */

/* functions of philo_control.c */

/* functions of philo_acts.c */

#endif