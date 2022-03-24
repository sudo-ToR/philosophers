/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:41 by tor               #+#    #+#             */
/*   Updated: 2022/03/24 22:40:39 by lnoirot          ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_philo
{
	int				id;
	char			*str_id;
	pthread_t 		thread;
	pthread_mutex_t	*available_fork[2];
	int				nb_meal;
	long			last_meal;
	int				is_dead;
	void			*global;
	int				last_action;
} t_philo;


typedef	struct s_fork
{
	int					id;
	pthread_mutex_t	thread;
}	t_fork;


typedef struct s_global
{
	int				nb_philo;
	int				nb_time_eat;
	long			time_death;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	pthread_mutex_t display;
 	t_fork			**fork;
	t_philo			**philo;
}	t_global;

int		parsing(char **arg, t_global *global);
int		create_fork(t_global *global);
int		create_philo(t_global *global);
long	get_time_stamp(t_global *global);
void	print_state_change(t_global *global, char *philo_id, int activity);
void	access_display(t_global *global, t_philo *philo, int activity);
void	death_philo(t_philo *philo);
void	eat_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		is_at_leat_one_philo_dead(t_global *global);
void	think_philo(t_philo *philo, long time_to_sleep);

#endif