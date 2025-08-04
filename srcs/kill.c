/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:27:49 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/28 09:40:13 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_philos(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!check_sim_stop(table))
	{
		i = 0;
		while (i < table->nb_philos)
		{
			pthread_mutex_lock(&table->philos[i]->meal_time_lock);
			if (get_time() - table->philos[i]->last_meal > table->time_to_die)
			{
				print_status(table->philos[i], "died");
				set_sim_stop(table);
				pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
			i++;
		}
		if (check_meals(table))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	check_sim_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->sim_stop_lock);
	stop = table->sim_stop;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (stop);
}

void	set_sim_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = 1;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

int	check_meals(t_table *table)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (table->must_eat_count == -1)
		return (0);
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (table->philos[i]->times_ate < table->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (all_ate)
		set_sim_stop(table);
	return (all_ate);
}
