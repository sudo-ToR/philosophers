/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:18:24 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/24 22:07:56 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		create_fork(t_global *global)
{
	int	i;
	
	global->fork = malloc(sizeof(t_fork *) * global->nb_philo);
	if (!global->fork)
		return (1);
	i = 0;
	while (i < global->nb_philo)
	{
		(global->fork)[i] = malloc(sizeof(t_fork));
		if (!(global->fork)[i])
			return (1);
		((global->fork)[i])->id = i + 1;
		if (pthread_mutex_init(&((global->fork)[i])->thread, NULL))
			return (1);
		i++;
	}
	return (0);
}