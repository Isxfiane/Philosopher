/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:14:33 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 14:50:33 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	request_write(t_state *state, char *str, int pos)
{
	pthread_mutex_lock(&state->write_m);
	if (check_end(state) == 1)
	{
		pthread_mutex_unlock(&state->write_m);
		return (1);
	}
	if (pos == 0)
		printf("%ld %s", get_time(state), str);
	else
		printf("%ld %d %s", get_time(state), pos, str);
	pthread_mutex_unlock(&state->write_m);
	return (0);
}

void	write_death(t_state *state, int i)
{
	long	time;

	pthread_mutex_lock(&state->somebody_dead_m);
	if (state->stop == 1)
	{
		pthread_mutex_unlock(&state->somebody_dead_m);
		return ;
	}
	state->stop = 1;
	pthread_mutex_unlock(&state->somebody_dead_m);
	time = get_time(state);
	pthread_mutex_lock(&state->write_m);
	printf(RED"%ld %d died"RESET"\n", time, i);
	pthread_mutex_unlock(&state->write_m);
}
