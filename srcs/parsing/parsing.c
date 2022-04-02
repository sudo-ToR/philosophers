/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:13:57 by lnoirot           #+#    #+#             */
/*   Updated: 2022/04/02 19:16:32 by lnoirot          ###   ########.fr       */
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

long	get_time_in_us(void)
{
	struct timeval	time;
	long			ret;

	if (gettimeofday(&time, 0))
		return (-1);
	ret = time.tv_sec * 1000000 + time.tv_usec;
	return (ret);
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

void	init_str_print(t_global	*global)
{
	global->state_print_str[FORK] = ft_strdup("has taken a fork");
	global->state_print_str[EAT] = ft_strdup("is eating");
	global->state_print_str[SLEEP] = ft_strdup("is sleeping");
	global->state_print_str[THINK] = ft_strdup("is thinking");
	global->state_print_str[DIE] = ft_strdup("died");
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
	global->start_time = get_time_in_us();
	if (!global->start_time)
		return (1);
	if (pthread_mutex_init(&global->display, NULL))
		return (1);
	if (pthread_mutex_init(&global->report_death, NULL))
		return (1);
	init_str_print(global);
	return (0);
}
