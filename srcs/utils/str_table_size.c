/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_table_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:33:14 by lnoirot           #+#    #+#             */
/*   Updated: 2022/03/23 15:33:29 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_table_size(char **table)
{
	int	len;

	len = 0;
	if (!table)
		return (len);
	while (table[len])
		len++;
	return (len);
}