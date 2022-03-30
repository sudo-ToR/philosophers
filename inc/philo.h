/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:49:41 by tor               #+#    #+#             */
/*   Updated: 2022/03/30 16:20:39 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "parsing.h"
# include "utils.h"
# include "threads.h"
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
	pthread_t		thread;
	pthread_mutex_t	*available_fork[2];
	pthread_mutex_t	meal;
	pthread_mutex_t	death;
	int				nb_meal;
	long			last_meal;
	pthread_mutex_t	meal_l;
	int				is_dead;
	void			*global;
	pthread_mutex_t	action;
	int				last_action;
}	t_philo;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		thread;
}	t_fork;

typedef struct s_global
{
	int				nb_philo;
	int				nb_time_eat;
	long			time_death;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	pthread_mutex_t	display;
	t_fork			**fork;
	t_philo			**philo;
	pthread_mutex_t	report_death;
	int				dead_philo;
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
int		have_starved(t_philo *philo);
int		check_death(t_global *global);
int		check_other_philo_mutex(t_global *global);
int		each_phil_has_eat_enough(t_global *global);
int		check_one_philo_death_mutex(t_philo *philo);
void	handle_single_philo(t_philo *philo);

#endif