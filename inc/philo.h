/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:41 by tor               #+#    #+#             */
/*   Updated: 2022/03/23 22:06:38 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "parsing.h"
# include "utils.h"
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			id;
	char		*str_id;
	pthread_t 	thread;
	pthread_t	available_fork[2];
	int			nb_meal;
	long	last_meal;
	void		*global;
} t_philo;


typedef	struct s_fork
{
	int					id;
	pthread_mutex_t	thread;
}	t_fork;


typedef struct s_global
{
	int			nb_philo;
	int			nb_time_eat;
	long		time_death;
	long		time_eat;
	long		time_sleep;
	long		start_time;
	t_fork		**fork;
	t_philo		**philo;
}	t_global;

int		parsing(char **arg, t_global *global);
int		create_fork(t_global *global);
int		create_philo(t_global *global);

#endif