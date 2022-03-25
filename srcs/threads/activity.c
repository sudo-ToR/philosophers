/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:19:06 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/25 22:33:20 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_philo(t_philo *philo, long time_to_sleep)
{
	t_global	*cast;

	cast = philo->global;
	access_display(cast, philo, THINK);
	philo->last_action = THINK;
	wait_end_activity(time_to_sleep);
}

void	sleep_philo(t_philo *philo)
{
	t_global	*cast;

	cast = philo->global;
	access_display(cast, philo, SLEEP);
	philo->last_action = SLEEP;
	wait_end_activity(cast->time_sleep);
}

void	death_philo(t_philo *philo)
{
	t_global	*cast;

	cast = philo->global;
	pthread_mutex_lock(&cast->display);
	pthread_mutex_lock(&philo->death);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->death);
	philo->last_action = DIE;
	print_state_change(cast, philo->str_id, DIE);
	pthread_mutex_unlock(&cast->display);
}

void	eat_philo(t_philo *philo)
{
	t_global	*cast;

	cast = philo->global;
	pthread_mutex_lock((philo->available_fork)[0]);
	access_display(cast, philo, FORK);
	if ((philo->available_fork)[1])
	{
		pthread_mutex_lock((philo->available_fork)[1]);
		access_display(cast, philo, FORK);
		pthread_mutex_lock(&philo->meal_l);
		philo->last_meal = get_time_in_ms();
		pthread_mutex_unlock(&philo->meal_l);
		access_display(cast, philo, EAT);
		pthread_mutex_lock(&philo->meal);
		philo->nb_meal += 1;
		pthread_mutex_unlock(&philo->meal);
		philo->last_action = EAT;
		wait_end_activity(cast->time_eat);
		pthread_mutex_unlock((philo->available_fork)[0]);
		pthread_mutex_unlock((philo->available_fork)[1]);
	}
}

void	*philosopher(void *arg)
{
	t_philo	*cast;

	cast = arg;
	if (cast->id % 2)
		cast->last_action = THINK;
	else
		cast->last_action = SLEEP;
	while (!cast->is_dead && !check_other_philo_mutex(cast->global)
		&& !each_phil_has_eat_enough(cast->global))
	{
		if (cast->last_action == THINK)
			eat_philo(cast);
		else if (cast->last_action == EAT)
			sleep_philo(cast);
		else if (cast->last_action == SLEEP)
			think_philo(cast, 50);
	}
	return (0);
}
