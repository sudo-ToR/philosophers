/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:13:57 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/30 22:06:20 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_at_least_one_arg_neg(t_global *global)
{
	if (global->nb_philo <= 0
		|| global->time_death <= 0
		|| global->time_eat <= 0
		|| global->time_sleep <= 0)
		return (1);
	return (0);
}

long	get_time_in_ms(void)
{
	struct timeval	time;
	long			ret;

	if (gettimeofday(&time, 0))
		return (-1);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

int	parsing(char **arg, t_global *global)
{
	global->nb_philo = ft_atoi(arg[0]);
	global->time_death = ft_atoi_long(arg[1]) * 1000;
	global->time_eat = ft_atoi_long(arg[2]) * 1000;
	global->time_sleep = ft_atoi_long(arg[3]) * 1000;
	global->nb_time_eat = -1;
	if (is_at_least_one_arg_neg(global))
		return (printf("Arguments has to be positiv \n"));
	if (str_table_size(arg) == 5)
		global->nb_time_eat = ft_atoi(arg[4]);
	if (str_table_size(arg) == 5 && global->nb_time_eat < 0)
		return (printf("Arguments has to be positiv\n"));
	if (str_table_size(arg) == 4)
		global->nb_time_eat = -1;
	global->start_time = get_time_in_ms();
	if (!global->start_time)
		return (1);
	if (pthread_mutex_init(&global->display, NULL))
		return (1);
	if (pthread_mutex_init(&global->report_death, NULL))
		return (1);
	return (0);
}
