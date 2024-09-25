/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:08:41 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/07 14:08:45 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	request_fork(t_state *state, int pos, int *rfork, int *lfork)
{
	pthread_mutex_lock(&state->forks_m[pos - 1]);
	if (state->forks[pos - 1] == 0)
		*rfork = take_forks(state, pos, 1);
	pthread_mutex_unlock(&state->forks_m[pos - 1]);
	if (state->philo_count == 1)
		return ;
	if (pos == state->philo_count)
	{
		pthread_mutex_lock(&state->forks_m[0]);
		if (state->forks[0] == 0)
			*lfork = take_forks(state, pos, pos);
		pthread_mutex_unlock(&state->forks_m[0]);
	}
	else
	{
		pthread_mutex_lock(&state->forks_m[pos]);
		if (state->forks[pos] == 0)
			*lfork = take_forks(state, pos, 0);
		pthread_mutex_unlock(&state->forks_m[pos]);
	}
}

int	take_forks(t_state *state, int pos, int minus)
{
	state->forks[pos - minus] = 1;
	if (request_write(state, FORK, pos) == 1)
		return (-1);
	return (1);
}

void	drop_fork(t_state *state, int pos)
{
	pthread_mutex_lock(&state->forks_m[pos - 1]);
	state->forks[pos - 1] = 0;
	pthread_mutex_unlock(&state->forks_m[pos - 1]);
	if (pos == state->philo_count)
	{
		pthread_mutex_lock(&state->forks_m[0]);
		state->forks[0] = 0;
		pthread_mutex_unlock(&state->forks_m[0]);
	}
	else
	{
		pthread_mutex_lock(&state->forks_m[pos]);
		state->forks[pos] = 0;
		pthread_mutex_unlock(&state->forks_m[pos]);
	}
}
