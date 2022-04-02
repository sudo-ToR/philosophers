/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:19:06 by lnoirot           #+#    #+#             */
/*   Updated: 2022/04/02 19:36:37 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_philo(t_philo *philo, long time_to_sleep, t_global *global)
{
	access_display(global, philo, THINK);
	wait_end_activity(time_to_sleep);
	pthread_mutex_lock(&philo->action);
	philo->last_action = THINK;
	pthread_mutex_unlock(&philo->action);
}

void	sleep_philo(t_philo *philo, t_global *global)
{
	access_display(global, philo, SLEEP);
	wait_end_activity(global->time_sleep);
	pthread_mutex_lock(&philo->action);
	philo->last_action = SLEEP;
	pthread_mutex_unlock(&philo->action);
}

void	death_philo(t_philo *philo, t_global *global)
{
	pthread_mutex_lock(&global->display);
	pthread_mutex_lock(&philo->death);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->death);
	pthread_mutex_lock(&philo->action);
	philo->last_action = DIE;
	pthread_mutex_unlock(&philo->action);
	print_state_change(global, philo->str_id, DIE);
	pthread_mutex_unlock(&global->display);
}

void	eat_philo(t_philo *philo, t_global *global)
{
	pthread_mutex_lock((philo->available_fork)[0]);
	access_display(global, philo, FORK);
	if ((philo->available_fork)[1])
	{
		pthread_mutex_lock((philo->available_fork)[1]);
		access_display(global, philo, FORK);
		access_display(global, philo, EAT);
		pthread_mutex_lock(&philo->meal_l);
		philo->last_meal = get_time_in_us();
		pthread_mutex_unlock(&philo->meal_l);
		pthread_mutex_lock(&philo->meal);
		philo->nb_meal += 1;
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_lock(&philo->action);
		philo->last_action = EAT;
		pthread_mutex_unlock(&philo->action);
		wait_end_activity(global->time_eat);
		pthread_mutex_unlock((philo->available_fork)[1]);
		pthread_mutex_unlock((philo->available_fork)[0]);
	}
}

void	*philosopher(void *arg)
{
	t_philo		*cast;
	int			action;

	cast = arg;
	if (((t_global *)(cast->global))->nb_philo == 1)
		handle_single_philo(cast);
	else
		attribute_first_action(cast);
	while (!check_one_philo_death_mutex(cast)
		&& !check_other_philo_mutex(cast->global)
		&& !each_phil_has_eat_enough(cast->global))
	{
		action = check_action_mutex(cast);
		if (action == THINK)
			eat_philo(cast, (t_global *)cast->global);
		else if (action == EAT)
			sleep_philo(cast, (t_global *)cast->global);
		else if (action == SLEEP)
			think_philo(cast, 5, (t_global *)cast->global);
	}
	return (0);
}
