/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:11:04 by tbellest          #+#    #+#             */
/*   Updated: 2025/02/18 15:58:00 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nb_philos)
	{
		table->philos[i]->last_meal = table->start_time;
		pthread_create(&table->philos[i]->thread, NULL, \
		philo_life, table->philos[i]);
		i++;
	}
	pthread_create(&table->killeuse, NULL, check_philos, table);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->killeuse, NULL);
}

void	clean_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		i++;
	}
	free(table->fork_locks);
	pthread_mutex_destroy(&table->sim_stop_lock);
	pthread_mutex_destroy(&table->write_lock);
	free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!is_valid_input(argc, argv))
		return (printf("Invalid input\n"), 1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	if (table->nb_philos == 1)
	{
		printf("%ld 1 is thinking\n", get_time() - table->start_time);
		usleep(table->time_to_die * 1000);
		printf("%ld 1 died\n", get_time() - table->start_time);
		clean_simulation(table);
		return (0);
	}
	start_simulation(table);
	clean_simulation(table);
	return (0);
}
