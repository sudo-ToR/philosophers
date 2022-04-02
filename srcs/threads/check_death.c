/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:24:37 by lnoirot           #+#    #+#             */
/*   Updated: 2022/04/02 19:33:49 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_other_philo_mutex(t_global *global)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&global->report_death);
	if (is_at_leat_one_philo_dead(global))
		ret = 1;
	pthread_mutex_unlock(&global->report_death);
	return (ret);
}

int	is_at_leat_one_philo_dead(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->nb_philo)
	{
		if ((global->philo)[i]
			&& check_one_philo_death_mutex((global->philo)[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_death(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->nb_philo)
	{
		if (have_starved((global->philo)[i], global))
		{
			pthread_mutex_lock(&(global->philo)[i]->action);
			(global->philo)[i]->last_action = DIE;
			pthread_mutex_unlock(&(global->philo)[i]->action);
			pthread_mutex_lock(&global->report_death);
			global->dead_philo = i + 1;
			pthread_mutex_lock(&(global->philo)[i]->death);
			(global->philo)[i]->is_dead = 1;
			pthread_mutex_unlock(&(global->philo)[i]->death);
			pthread_mutex_unlock(&global->report_death);
			return (1);
		}
	}
	return (0);
}

int	check_last_meal_mutex(t_philo *philo)
{
	long	ret;

	ret = 0;
	pthread_mutex_lock(&philo->meal_l);
	if (philo->last_meal)
		ret = get_time_in_us() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_l);
	return (ret);
}

int	have_starved(t_philo *philo, t_global *global)
{
	if (global->nb_philo > 1
		&& check_last_meal_mutex (philo) > global->time_death)
		return (1);
	else if (global->nb_philo == 1
		&& get_time_in_us() - global->start_time >= global->time_death)
		return (1);
	return (0);
}
