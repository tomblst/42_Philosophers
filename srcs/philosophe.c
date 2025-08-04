/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:53 by tbellest          #+#    #+#             */
/*   Updated: 2025/02/18 16:02:35 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_sim_stop(philo->table))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_status(philo, "is sleeping");
		sleeping(philo->table->time_to_sleep, philo->table);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->meal_time_lock);
	print_status(philo, "is eating");
	sleeping(philo->table->time_to_eat, philo->table);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!check_sim_stop(philo->table))
		printf("%ld %d %s\n", get_time() - \
		philo->table->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_lock);
}
