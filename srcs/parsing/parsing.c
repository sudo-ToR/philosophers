/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:13:57 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/23 16:10:26 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	is_at_least_one_arg_neg(t_philo *philo)
{
	if (philo->nb_philo < 0
		|| philo->time_death < 0
		|| philo->time_eat < 0
		|| philo->time_sleep < 0)
		return (1);
	return(0);
}

int		parsing(char **arg, t_philo *philo)
{
	philo->nb_philo = ft_atoi(arg[0]);
	philo->time_death = ft_atoi_double(arg[1]);
	philo->time_eat = ft_atoi_double(arg[2]);
	philo->time_sleep = ft_atoi_double(arg[3]);
	if (is_at_least_one_arg_neg(philo))
	{
		printf("Arguments has to be positiv \n");
		return (1);
	}
	if (str_table_size(arg) == 5)
		philo->nb_time_eat = ft_atoi(arg[4]);
	if (philo->nb_time_eat < 0)
	{
		printf("Arguments has to be positiv \n");
		return (1);
	}
	if (str_table_size(arg)== 4)
		philo->nb_time_eat = -1;
	return(0);
}