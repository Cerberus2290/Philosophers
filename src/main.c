/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:05:56 by tstrassb          #+#    #+#             */
/*   Updated: 2023/04/20 14:29:57 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_control	*data;

	if (check_input(argc, argv) != 0)
		return (-1);
	data = (t_control *)ft_calloc(1, sizeof(t_control));
	if (!data)
		return (-1);
	init_s_control(argv, data);
	philo_start(data);
	philo_end(data);
	return (0);
}
