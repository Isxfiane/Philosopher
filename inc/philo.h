/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:34:11 by sben-rho          #+#    #+#             */
/*   Updated: 2024/06/28 11:50:36 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define EATING "is eating\n"
# define FORK "has taken a fork\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

struct		s_state;
typedef struct s_philo
{
	int						position;
	time_t					death_time;
	int						eat_count;
	int						lfork;
	int						rfork;
	struct s_state			*state;
	pthread_mutex_t			deathtime_m;
	pthread_mutex_t			iseating_m;
}					t_philo;

typedef struct s_state
{
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	void					**philo;
	time_t					start;
	pthread_mutex_t			*forks_m;
	int						*forks;
	pthread_mutex_t			write_m;
	pthread_mutex_t			start_m;
	pthread_mutex_t			somebody_dead_m;
	int						stop;
}					t_state;

/*---| Utils |---*/
int			ft_atoi(const char *nptr);
long		get_time(t_state *state);
void		ft_usleep(long int time_in_ms, t_state *state);
int			check_args(t_state *state);
void		fail_philo(int i, t_state *state, pthread_t *threads);
/*---------------*/

/*---| Fork |---*/
void		request_fork(t_state *state, int pos, int *rfork, int *lfork);
int			take_forks(t_state *state, int pos, int minus);
void		drop_fork(t_state *state, int pos);
/*---|------|---*/

/*---| Init & Destroy |---*/
void		init_fork_mutex(t_state *state);
int			init_state(t_state *state, int argc, char **argv);
t_philo		*init_philo(t_state *state, int pos);
pthread_t	*init_threads(t_state *state);

int			destroy_state(t_state *state);
void		kill_threads(pthread_t *threads, t_state *state);
/*---|------|---*/

/*---| Routine |---*/
void		*routine(void *arg);
int			check_end(t_state *state);
int			check_death_philo(t_state *state, int pos);
void		*supervisor(void *args);
/*---|------|---*/

/*---| Write |---*/
int			request_write(t_state *state, char *str, int pos);
void		write_death(t_state *state, int i);
/*---|------|---*/

/*---| Eat |---*/
int			eat(t_philo *philo);
int			check_must_eat(t_state *state);
int			check_eat_philo(t_state *state, int pos);
int			check_eat_count(t_state *state);
/*---|------|---*/
#endif