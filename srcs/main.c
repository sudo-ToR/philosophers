/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:36 by tor               #+#    #+#             */
/*   Updated: 2022/03/23 16:08:46 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	if (ac < 5 || ac > 8)
	{
		printf("Wong number of arguments \n");
		return (1);
	}
	if (parsing(&av[1], &philo))
		return (1);
	printf("nb philo %d\ntime death %f\ntime eat %f\ntime sleep %f\nnb time eat %d\n",
		philo.nb_philo, philo.time_death, philo.time_eat, philo.time_sleep, philo.nb_time_eat);
	return (0);
}