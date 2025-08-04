/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/02/18 16:09:14 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->sim_stop = 0;
	pthread_mutex_init(&table->sim_stop_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	table->fork_locks = init_fork_mutexes(table);
	table->philos = init_philos(table);
	table->start_time = get_time();
	return (table);
}

pthread_mutex_t	*init_fork_mutexes(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	**init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo *) * table->nb_philos);
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->id = i + 1;
		philos[i]->times_ate = 0;
		philos[i]->fork[0] = i;
		philos[i]->fork[1] = (i + 1) % table->nb_philos;
		pthread_mutex_init(&philos[i]->meal_time_lock, NULL);
		philos[i]->last_meal = get_time();
		philos[i]->table = table;
		i++;
	}
	return (philos);
}
