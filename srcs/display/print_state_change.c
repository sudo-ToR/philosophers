/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:56 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/30 16:03:02 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_global *global, char *philo_id, int activity)
{
	long	timestamp;
	char	*str;

	timestamp = get_time_stamp(global);
	str = NULL;
	if (activity == FORK)
		str = ft_strdup("has taken a fork");
	else if (activity == EAT)
		str = ft_strdup("is eating");
	else if (activity == SLEEP)
		str = ft_strdup("is sleeping");
	else if (activity == THINK)
		str = ft_strdup("is thinking");
	else if (activity == DIE)
		str = ft_strdup("died");
	printf("%zu %s %s\n", timestamp, philo_id, str);
	free(str);
}
