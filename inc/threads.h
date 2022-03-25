/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:21:08 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/25 16:23:42 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H

# define  THREADS_H

void	wait_end_activity(long time_to_wait);
void	*philosopher(void *arg);

#endif