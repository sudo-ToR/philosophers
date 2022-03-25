/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:14:34 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/25 18:52:54 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	access_display(t_global *global, t_philo *philo, int activity)
{
	if (!global->dead_philo)
	{
		pthread_mutex_lock(&global->display);
		print_state_change(global, philo->str_id, activity);
		pthread_mutex_unlock(&global->display);
	}
}
