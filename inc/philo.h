/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:37:48 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/26 12:28:18 by tstrassb         ###   ########.fr       */
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
# define ERR_CMD "Syntax error. Use: ./philo [number_of_philos] [time_to_die] [time_to_eat]\
 [time_to_sleep] (OPTIONAL - [number_time_must_eat])\n"
# define ERR_MAX "ERR_MAX\n"
# define ERR_ARGS "ERR_ARGS\n"

typedef struct s_control	t_control;
typedef struct s_philo		t_philo;

/* struct to store all info about philosophers */
typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	int				meals_eaten;
	long long		t_lastmeal;
	pthread_mutex_t	lastmeal_mutex;
	int				l_fork;
	int				r_fork;
	t_control		*args;
}	t_philo;

/* struct to store info about eat, sleep, die */
typedef struct s_control
{
	int				nb_philo;
	long long		t0;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				max_meals;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	cout;
	pthread_mutex_t	checker;
	pthread_mutex_t	game_over_mutex;
	int				error;
	int				end_meal;
	int				game_over;
}	t_control;

/* functions of init.c */

int			check_input(int argc, char **argv);
void		init_s_control(char **argv, t_control *input);
void		init_s_philo(t_control *input);

/* functions of timeutils.c */

long long	start_time(void);
long long	timestamp(t_control *input);
void		ft_sleep(t_philo *p, int t_wait);

/* functions of utils.c */

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		philo_print(t_philo *p, char *state);

/* functions of philo_control.c */

void		philo_start(t_control *input);
void		*philo_act(void *p);
void		checking(t_control *c);
void		check_death(t_philo *p);
void		philo_over(t_control *input);

/* functions of philo_acts.c */

void		*one_philo(void *p);
void		philo_eats(t_philo *ph);
void		philo_thinks(t_philo *ph);
void		philo_sleeps(t_philo *ph);

#endif