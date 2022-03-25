/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:17 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/25 16:22:44 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_stamp(t_global *global)
{
	return (get_time_in_ms() - global->start_time);
}

void	wait_end_activity(long time_to_wait)
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
