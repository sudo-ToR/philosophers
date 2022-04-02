/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:17 by lnoirot           #+#    #+#             */
/*   Updated: 2022/04/02 19:17:59 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_stamp(t_global *global)
{
	return ((get_time_in_us() - global->start_time) / 1000);
}

void	wait_end_activity(long time_to_wait)
{
	long	start;
	long	in_progress;

	in_progress = 0;
	start = get_time_in_us();
	while (time_to_wait >= in_progress)
	{
		usleep(50);
		in_progress = get_time_in_us() - start;
	}
}
