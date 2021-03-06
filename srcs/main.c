/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:36 by tor               #+#    #+#             */
/*   Updated: 2022/04/02 19:04:24 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct_global(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->nb_philo)
	{
		free((global->fork)[i]);
		free((global->philo)[i]->str_id);
		free((global->philo)[i]);
		i++;
	}
	free(global->fork);
	free(global->philo);
	i = 0;
	while (i < 5)
	{
		free(global->state_print_str[i]);
		i++;
	}
}

void	check_global_dead_philo_mutex(t_global *global)
{
	pthread_mutex_lock(&global->report_death);
	if (global->dead_philo)
	{
		death_philo((global->philo)[global->dead_philo - 1], global);
		pthread_mutex_unlock(&global->report_death);
	}
	else
		pthread_mutex_unlock(&global->report_death);
}

int	main(int ac, char **av)
{
	t_global	global;
	int			i;

	i = -1;
	memset(&global, 0, sizeof(t_global));
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments \n");
		return (1);
	}
	if (parsing(&av[1], &global))
		return (1);
	create_fork(&global);
	create_philo(&global);
	while (!global.dead_philo && !each_phil_has_eat_enough(&global))
		check_death(&global);
	check_global_dead_philo_mutex(&global);
	while (++i < global.nb_philo)
		pthread_join((global.philo[i])->thread, NULL);
	free_struct_global(&global);
	return (0);
}
