/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:20:46 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/23 21:51:30 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
	t_philo	*cast;

	cast = arg;
	printf("In thread %d\n", cast->id);
	return (0);
}

// void	fill_avalaible_fork(t_philo **philo, void *global)
// {
	
// }

void	init_philo(t_philo **philo, int id, void *global)
{
	(*philo)->id = id;
	(*philo)->global = global;
	(*philo)->nb_meal = 0;
	(*philo)->str_id= ft_itoa((*philo)->id);
	(*philo)->last_meal = -1;

}

int	create_philo(t_global *global)
{
	int	i;

	global->philo = malloc(sizeof (t_philo *) * global->nb_philo);
	if (!global->philo)
		return (1);
	i = 0;
	while(i < global->nb_philo)
	{
		(global->philo)[i] = malloc(sizeof(t_philo));
		if (!(global->philo)[i])
			return(1);
		init_philo(&(global->philo)[i], i + 1, global);
		if (pthread_create(&((global->philo)[i])->thread, NULL, test, (global->philo)[i]))
			return (1);
		i++;
	}
	return (0);
}