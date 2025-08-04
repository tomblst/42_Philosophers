/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:43:39 by tbellest          #+#    #+#             */
/*   Updated: 2025/02/18 16:13:20 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeping(time_t time, t_table *table)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_sim_stop(table))
			break ;
		usleep(100);
	}
}
