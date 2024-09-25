/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:33:52 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 13:19:59 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_m[0]);
	pthread_mutex_unlock(&philo->state->forks_m[0]);
	if (philo->position % 2 == 0)
	{
		pthread_mutex_lock(&philo->state->start_m);
		pthread_mutex_unlock(&philo->state->start_m);
	}
}

int	check_end(t_state *state)
{
	pthread_mutex_lock(&state->somebody_dead_m);
	if (state->stop == 1)
	{
		pthread_mutex_unlock(&state->somebody_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&state->somebody_dead_m);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	start(philo);
	while (check_end(philo->state) == 0)
	{
		while (philo->lfork == 0 || philo->rfork == 0)
		{
			request_fork(philo->state, philo->position,
				&philo->rfork, &philo->lfork);
			if (philo->lfork == -1 || philo->rfork == -1
				|| check_end(philo->state) == 1)
				break ;
			usleep(1);
		}
		if (eat(philo) == 1)
			break ;
		if (request_write(philo->state, SLEEPING, philo->position) == 1)
			break ;
		ft_usleep(philo->state->time_to_sleep, philo->state);
		if (request_write(philo->state, THINKING, philo->position) == 1)
			break ;
	}
	return (free(philo), NULL);
}
