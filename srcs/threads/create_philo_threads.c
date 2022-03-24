/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:20:46 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/24 22:32:20 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_at_leat_one_philo_dead(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->nb_philo)
	{
		if ((global->philo)[i]->is_dead)
			return (1);
		i++;
	}
	return (0);
}

void	wait_end_activity(long	time_to_wait)
{
	long	start;
	long	in_progress;

	in_progress = 0;
	start = get_time_in_ms();
	while (time_to_wait >= in_progress)
	{
		usleep(50);
		in_progress = (get_time_in_ms() - start) * 1000;
	}
}

int		have_starved(t_philo *philo)
{
	t_global	*cast;

	cast = philo->global;
	if (philo->last_meal - get_time_in_ms() > cast->time_death)
		return (1);
	return (0);
}

void	*test(void *arg)
{
	t_philo	*cast;

	cast = arg;
	if (cast->id % 2)
		cast->last_action = THINK;
	else
		cast->last_action = SLEEP;
	while (!cast->is_dead)
	{
		if (cast->last_action == THINK)
			eat_philo(cast);
		else if (cast->last_action == EAT)
			sleep_philo(cast);
		else if (cast->last_action == SLEEP)
			think_philo(cast, 5000);
		cast->is_dead = have_starved(cast);
	}
		if (cast->is_dead)
			death_philo(cast);
	return (0);
}


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
	t_global *cast;

	cast = philo->global;
	access_display(cast, philo, SLEEP);
	philo->last_action = SLEEP;
	wait_end_activity(cast->time_sleep);
}

void	access_display(t_global *global, t_philo *philo, int activity)
{
	pthread_mutex_lock(&global->display);
	print_state_change(global, philo->str_id, activity);
	pthread_mutex_unlock(&global->display);
}

void	death_philo(t_philo *philo)
{
	t_global	*cast;

	cast = philo->global;
	pthread_mutex_lock(&cast->display);
	philo->is_dead = 1;
	philo->last_action = DIE;
	print_state_change(cast, philo->str_id, DIE);
}

void	eat_philo(t_philo *philo)
{
	t_global *cast;

	cast = philo->global;
	pthread_mutex_lock(&(philo->available_fork)[0]);
	access_display(cast, philo, FORK);
	pthread_mutex_lock(&(philo->available_fork)[1]);
	access_display(cast, philo, FORK);
	access_display(cast, philo, EAT);
	philo->last_meal = get_time_in_ms();
	philo->nb_meal += 1;
	philo->last_action = EAT;
	wait_end_activity(cast->time_eat);
	pthread_mutex_unlock(&(philo->available_fork)[0]);
	pthread_mutex_unlock(&(philo->available_fork)[1]);	
}

void	print_state_change(t_global *global, char *philo_id, int activity)
{
	long	timestamp;
	char	*str;

	timestamp = get_time_stamp(global);
	str = NULL;
	if (activity == FORK)
		str = ft_strdup("has taken a fork");
	else if (activity == EAT)
		str = ft_strdup("is_eating");
	else if (activity == SLEEP)
		str = ft_strdup("is sleeping");
	else if (activity == THINK)
		str = ft_strdup("is thinking");
	else if (activity == DIE)
		str = ft_strdup("died");
	printf("%zu %s %s\n", timestamp, philo_id, str);
	free(str);
}

long	get_time_stamp(t_global *global)
{
	return (get_time_in_ms() - global->start_time);
}

void	init_philo(t_philo **philo, int id, t_global *global)
{
	(*philo)->id = id;
	(*philo)->global = global;
	(*philo)->nb_meal = 0;
	(*philo)->str_id= ft_itoa((*philo)->id);
	(*philo)->last_meal = -1;
	(*philo)->is_dead = 0;
	printf("id: %d\n", (*philo)->id);
	if (id != global->nb_philo)
	{
		printf("NOT LAST, (%d, %d)\n", id - 1, id);
		((*philo)->available_fork)[0] = ((global->fork)[id - 1])->thread;
		((*philo)->available_fork)[1] = ((global->fork)[id])->thread;
	}
	// else if (id == 1)
	// {
	// 	((*philo)->available_fork)[0] = ((global->fork)[id - 1])->thread;
	// 	((*philo)->available_fork)[1] = ((global->fork)[global->nb_philo - 1])->thread;
	// }
	else
	{
		printf("LAST, (0, %d)\n", id - 1);
		((*philo)->available_fork)[0] = ((global->fork)[0])->thread;
		((*philo)->available_fork)[1] = ((global->fork)[id - 1])->thread;
	}
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