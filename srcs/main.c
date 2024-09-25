/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:34:07 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 12:32:47 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_philo(t_state *state, int pos)
{
	t_philo	*philo;

	philo = state->philo[pos - 1];
	pthread_mutex_lock(&philo->deathtime_m);
	if (get_time(state) > philo->death_time)
	{
		pthread_mutex_unlock(&philo->deathtime_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->deathtime_m);
	return (0);
}

void	*supervisor(void *args)
{
	int		i;
	t_state	*state;

	state = (t_state *)args;
	while (check_end(state) == 0)
	{
		i = 1;
		while (i <= state->philo_count)
		{
			if (check_death_philo(state, i) == 1)
			{
				write_death(state, i);
				return (NULL);
			}
			else
				i++;
			usleep(25);
		}
		if (check_eat_count(state) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_state			state;
	pthread_t		*threads;
	pthread_t		supervi;

	if (argc != 5 && argc != 6)
		return (printf(RED"Error: wrong number of arguments\n"RESET), 1);
	if (init_state(&state, argc, argv) == 1)
		return (1);
	pthread_mutex_lock(&state.forks_m[0]);
	if (state.philo_count != 1)
		pthread_mutex_lock(&state.start_m);
	threads = init_threads(&state);
	if (!threads)
		return (destroy_state(&state));
	state.start = get_time(&state);
	pthread_create(&supervi, NULL, &supervisor, &state);
	pthread_mutex_unlock(&state.forks_m[0]);
	if (state.philo_count != 1)
	{
		ft_usleep(state.time_to_eat / 2, &state);
		pthread_mutex_unlock(&state.start_m);
	}
	pthread_join(supervi, NULL);
	kill_threads(threads, &state);
	return (0);
}
