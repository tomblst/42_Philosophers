/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:08:59 by tbellest          #+#    #+#             */
/*   Updated: 2025/02/18 16:06:26 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	int				nb_philos;
	pthread_t		killeuse;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	int				sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_ate;
	int					fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

//main.c
int				main(int argc, char **argv);

//parsing.c
int				ft_isdigit(char *str);
int				is_valid_input(int argc, char **argv);
int				ft_atoi(const char *str);

//init.c
t_table			*init_table(int argc, char **argv);
t_philo			**init_philos(t_table *table);
pthread_mutex_t	*init_fork_mutexes(t_table *table);

//time.c
time_t			get_time(void);

//philosophe.c
void			*philo_life(void *philo);
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			drop_forks(t_philo *philo);
void			sleeping(time_t time, t_table *table);
void			print_status(t_philo *philo, char *status);

//kill.c
void			*check_philos(void *arg);
int				check_sim_stop(t_table *table);
void			set_sim_stop(t_table *table);
int				check_meals(t_table *table);

#endif
