/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:36 by tor               #+#    #+#             */
/*   Updated: 2022/03/23 22:13:51 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_global	global;

	memset(&global, 0, sizeof(t_global));
	if (ac < 5 || ac > 8)
	{
		printf("Wong number of arguments \n");
		return (1);
	}
	if (parsing(&av[1], &global))
		return (1);
	printf("nb philo %d\ntime death %zu\ntime eat %zu\ntime sleep %zu\nnb time eat %d\n",
		global.nb_philo, global.time_death, global.time_eat, global.time_sleep, global.nb_time_eat);
	create_fork(&global);
	create_philo(&global);
	return (0);
}