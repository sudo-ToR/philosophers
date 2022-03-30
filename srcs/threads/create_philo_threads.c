/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:20:46 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/30 15:19:59 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_one_philo_death_mutex(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->death);
	if (philo->is_dead)
		ret = 1;
	pthread_mutex_unlock(&philo->death);
	return (ret);
}

void	init_philo(t_philo **philo, int id, t_global *global)
{
	(*philo)->id = id;
	(*philo)->global = global;
	(*philo)->nb_meal = 0;
	(*philo)->str_id = ft_itoa((*philo)->id);
	(*philo)->last_meal = 0;
	pthread_mutex_init(&(*philo)->death, NULL);
	pthread_mutex_lock(&(*philo)->death);
	(*philo)->is_dead = 0;
	pthread_mutex_unlock(&(*philo)->death);
	if (id != global->nb_philo)
	{
		((*philo)->available_fork)[0] = &((global->fork)[id - 1])->thread;
		((*philo)->available_fork)[1] = &((global->fork)[id])->thread;
	}
	else
	{
		((*philo)->available_fork)[0] = &((global->fork)[0])->thread;
		((*philo)->available_fork)[1] = &((global->fork)[id - 1])->thread;
	}
	if (global->nb_philo == 1)
		((*philo)->available_fork)[1] = 0;
	pthread_mutex_init(&(*philo)->meal, NULL);
	pthread_mutex_init(&(*philo)->meal_l, NULL);
	pthread_mutex_init(&(*philo)->action, NULL);
}

int	create_philo(t_global *global)
{
	int	i;

	global->philo = malloc(sizeof (t_philo *) * global->nb_philo);
	if (!global->philo)
		return (1);
	i = 0;
	while (i < global->nb_philo)
	{
		(global->philo)[i] = malloc(sizeof(t_philo));
		if (!(global->philo)[i])
			return (1);
		init_philo(&(global->philo)[i], i + 1, global);
		i++;
	}
	i = 0;
	while (i < global->nb_philo)
	{
		if (pthread_create(&((global->philo)[i])->thread,
			NULL, philosopher, (global->philo)[i]))
			return (1);
		i++;
	}
	return (0);
}
