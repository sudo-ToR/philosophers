/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:36 by tor               #+#    #+#             */
/*   Updated: 2022/03/24 21:48:27 by lnoirot          ###   ########.fr       */
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
	create_fork(&global);
	create_philo(&global);
	while (!is_at_leat_one_philo_dead(&global))
		continue;
	return (0);
}
