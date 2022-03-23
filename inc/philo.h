/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:41 by tor               #+#    #+#             */
/*   Updated: 2022/03/23 15:30:24 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "parsing.h"
# include "utils.h"
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	int		nb_philo;
	int		nb_time_eat;
	double	time_death;
	double	time_eat;
	double	time_sleep;
}	t_philo;

int		parsing(char **arg, t_philo *philo);

#endif