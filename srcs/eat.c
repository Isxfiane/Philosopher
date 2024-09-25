/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:00:51 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 14:51:08 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat_count(t_state *state)
{
	long	time;

	if (check_must_eat(state) == 1)
	{
		time = get_time(state);
		pthread_mutex_lock(&state->somebody_dead_m);
		state->stop = 1;
		pthread_mutex_unlock(&state->somebody_dead_m);
		pthread_mutex_lock(&state->write_m);
		printf(GREEN"Must eat reach by all, ending simulation"RESET"\n");
		pthread_mutex_unlock(&state->write_m);
		return (1);
	}
	return (0);
}

int	check_eat_philo(t_state *state, int pos)
{
	t_philo	*philo;

	philo = state->philo[pos - 1];
	pthread_mutex_lock(&philo->iseating_m);
	if (philo->eat_count >= state->must_eat_count)
	{
		pthread_mutex_unlock(&philo->iseating_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->iseating_m);
	return (0);
}

int	check_must_eat(t_state *state)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (state->must_eat_count == -1)
		return (0);
	while (i <= state->philo_count)
	{
		if (check_eat_philo(state, i) == 1)
			count++;
		i++;
		usleep(50);
	}
	if (count == state->philo_count)
		return (1);
	return (0);
}

int	eat(t_philo *philo)
{
	long	time;

	if (request_write(philo->state, EATING, philo->position) == 1)
		return (1);
	time = get_time(philo->state);
	pthread_mutex_lock(&philo->deathtime_m);
	philo->death_time = time + philo->state->time_to_die;
	pthread_mutex_unlock(&philo->deathtime_m);
	ft_usleep(philo->state->time_to_eat - (get_time(philo->state) - time),
		philo->state);
	pthread_mutex_lock(&philo->iseating_m);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->iseating_m);
	drop_fork(philo->state, philo->position);
	philo->lfork = 0;
	philo->rfork = 0;
	return (0);
}
