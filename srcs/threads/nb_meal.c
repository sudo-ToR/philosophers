/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:34:19 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/30 22:16:37 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_action_mutex(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->action);
	ret = philo->last_action;
	pthread_mutex_unlock(&philo->action);
	return (ret);
}

void	attribute_first_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->action);
	if (philo->id % 2)
		philo->last_action = THINK;
	else
		philo->last_action = SLEEP;
	pthread_mutex_unlock(&philo->action);
}

int	check_with_mutex_meal(t_global *global, t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->meal);
	if (philo->nb_meal < global->nb_time_eat)
		ret = 1;
	pthread_mutex_unlock(&philo->meal);
	return (ret);
}

int	each_phil_has_eat_enough(t_global *global)
{
	int	i;

	i = 0;
	if (global->nb_time_eat < 0)
		return (0);
	while (global->philo && i < global->nb_philo && (global->philo)[i])
	{
		if (check_with_mutex_meal(global, (global->philo)[i]))
			return (0);
		i++;
	}
	return (1);
}
