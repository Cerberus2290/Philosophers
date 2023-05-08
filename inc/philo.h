/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:37:48 by tstrassb          #+#    #+#             */
/*   Updated: 2023/05/08 14:49:44 by tstrassb         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				number;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				meals;
	long long		st_time;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	meals_mutex;
	int				meals_eaten;
	pthread_mutex_t	death_mutex;
	int				death;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	st_eating_mutex;
	long long int	started_eating;
	pthread_t		philo_thread;
	pthread_mutex_t	mutex_l_fork;
	pthread_mutex_t	*mutex_r_fork;
	t_data			*data;
}	t_philo;

/* functions death.c */

int			check_death(t_philo **ph);
int			handle_death(t_data *data, t_philo **ph);

/* functions eat.c */

int			check_meals_eaten(t_philo **ph);
int			check_eating_time(t_philo **ph, int i, int id);
void		add_meals_eaten(t_philo **ph);
int			take_l_fork(t_philo **ph);
void		philo_eat(t_philo **ph, int fork);

/* functions init.c */

t_data		init_struct(char **argv);
int			init_mutexes(t_data *data);

/* functions lib.c */

int			ft_atoi(char *str);
long int	ft_atol(char *str);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);

/* functions philo.c */

int			create_threads(t_philo **ph);
int			join_threads(t_philo **ph, int philoid);
t_philo		*init_philo(t_data *data);
void		protect_datamutexes(t_philo **ph);

/* functions print.c */

void		philo_print(t_philo **ph, char *str);
void		philo_sleep(t_philo **ph, int nb);

/* functions routine.c */

void		*philo_routine(t_philo *ph);
void		sleep_function(t_philo **ph, long long msec);
long long	gettime(void);

/* functions utils.c */

void		clear_data(t_data *data);
void		clear_philo(t_philo **ph, int forknbr, int eatnbr, int philonbr);
int			*parse_and_check(char **argv, int *args);

#endif