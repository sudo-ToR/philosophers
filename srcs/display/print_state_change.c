/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:56 by lnoirot           #+#    #+#             */
/*   Updated: 2022/04/02 16:54:17 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_global *global, char *philo_id, int activity)
{
	long	timestamp;

	timestamp = get_time_stamp(global);
	printf("%zu %s %s\n", timestamp, philo_id,
		global->state_print_str[activity]);
}
