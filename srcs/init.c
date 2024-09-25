/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:41:44 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 13:20:09 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*create_tab(int size)
{
	int	*tab;
	int	i;

	i = 0;
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

void	init_fork_mutex(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philo_count)
	{
		pthread_mutex_init(&state->forks_m[i], NULL);
		i++;
	}
}

int	init_state(t_state *state, int argc, char **argv)
{
	state->philo_count = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat_count = ft_atoi(argv[5]);
	else
		state->must_eat_count = -1;
	if (check_args(state) == 1)
		return (printf("Error: Invalid arguments\n"), 1);
	state->start = 0;
	state->forks_m = malloc(sizeof(pthread_mutex_t) * (state->philo_count + 1));
	if (!state->forks_m)
		return (1);
	state->forks = create_tab(state->philo_count + 1);
	if (!state->forks)
		return (1);
	state->start = 0;
	state->stop = 0;
	init_fork_mutex(state);
	pthread_mutex_init(&state->write_m, NULL);
	pthread_mutex_init(&state->somebody_dead_m, NULL);
	pthread_mutex_init(&state->start_m, NULL);
	return (0);
}

t_philo	*init_philo(t_state *state, int pos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->position = pos;
	philo->eat_count = 0;
	philo->state = state;
	philo->lfork = 0;
	philo->rfork = 0;
	philo->death_time = state->time_to_die;
	pthread_mutex_init(&philo->iseating_m, NULL);
	pthread_mutex_init(&philo->deathtime_m, NULL);
	return (philo);
}

pthread_t	*init_threads(t_state *state)
{
	pthread_t	*threads;
	int			i;

	state->philo = malloc(sizeof(void *) * state->philo_count);
	threads = malloc(sizeof(pthread_t) * state->philo_count);
	if (!state->philo || !threads)
		return (NULL);
	i = 0;
	while (i < state->philo_count)
	{
		state->philo[i] = init_philo(state, i + 1);
		if (!state->philo[i] || pthread_create(&threads[i], NULL,
				&routine, state->philo[i]) != 0)
		{
			fail_philo(i, state, threads);
			return (NULL);
		}
		usleep(1);
		i++;
	}
	return (threads);
}
