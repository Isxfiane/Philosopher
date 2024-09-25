/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:41:41 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/06 13:41:51 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i = i + 1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

long	get_time(t_state *state)
{
	struct timeval	time;
	long			time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms - state->start);
}

void	ft_usleep(long int time_in_ms, t_state *state)
{
	long int	start_time;

	start_time = get_time(state);
	usleep((time_in_ms * 1000) / 2);
	while (start_time + time_in_ms > get_time(state))
		usleep(50);
}

int	check_args(t_state *state)
{
	int	status;

	status = 0;
	if (state->philo_count <= 0)
		status = 1;
	if (state->time_to_die <= 0)
		status = 1;
	if (state->time_to_eat <= 0)
		status = 1;
	if (state->time_to_sleep <= 0)
		status = 1;
	if (state->must_eat_count <= 0 && state->must_eat_count != -1)
		status = 1;
	return (status);
}

void	fail_philo(int i, t_state *state, pthread_t *threads)
{
	while (i >= 0)
	{
		free(state->philo[i]);
		pthread_detach(threads[i]);
		i--;
	}
}
