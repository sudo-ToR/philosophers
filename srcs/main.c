/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:36 by tor               #+#    #+#             */
/*   Updated: 2022/03/25 22:12:23 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_global	global;
	int			i;

	i = -1;
	memset(&global, 0, sizeof(t_global));
	if (ac != 5 && ac != 6)
	{
		printf("Wong number of arguments \n");
		return (1);
	}
	if (parsing(&av[1], &global))
		return (1);
	create_fork(&global);
	create_philo(&global);
	while (!global.dead_philo && !each_phil_has_eat_enough(&global))
		check_death(&global);
	if (global.dead_philo)
		death_philo(global.philo[global.dead_philo - 1]);
	while (++i < global.nb_philo)
		pthread_join((global.philo[i])->thread, NULL);
	return (0);
}
