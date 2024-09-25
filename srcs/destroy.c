/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:47:42 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/26 10:31:09 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_state(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philo_count)
	{
		pthread_mutex_destroy(&state->forks_m[i]);
		i++;
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
	free(state->forks_m);
	free(state->forks);
	free(state->philo);
	return (1);
}

void	kill_threads(pthread_t *threads, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	destroy_state(state);
}
