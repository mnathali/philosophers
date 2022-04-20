/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:59:42 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/20 21:34:12 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

char	first_fork(t_list_chops *philosopher, int (*f)(pthread_mutex_t *))
{
	if (philosopher->i % 2)
		f(&philosopher->m);
	else
		f(&philosopher->next->m);
	return (1);
}

void	second_fork(t_list_chops *philosopher)
{
	if (philosopher->i % 2)
		pthread_mutex_lock(&philosopher->next->m);
	else
		pthread_mutex_lock(&philosopher->m);
}

char	unlock_all(t_list_chops *philosopher)
{
	pthread_mutex_unlock(&philosopher->m);
	pthread_mutex_unlock(&philosopher->next->m);
	return (1);
}

void	eat_and_sleep(t_list_chops *philosopher, struct timeval *tv)
{
	print("%ld %d has taken a fork\n", philosopher);
	print("%ld %d is eating\n", philosopher);
	my_sleep(philosopher->info[2]);
	unlock_all(philosopher);
	gettimeofday(tv, 0);
	if (philosopher->times_of_eat > 0)
		philosopher->times_of_eat -= 1;
	if (philosopher->info[5] != -1)
	{
		print("%ld %d is sleeping\n", philosopher);
		my_sleep(philosopher->info[3]);
	}
	return ;
}

void	*philosophers_routine(void *data)
{
	t_list_chops	*philosopher;
	struct timeval	tv;

	philosopher = (t_list_chops *)data;
	while (philosopher->info[5] == 1)
		usleep(1);
	while (philosopher->info[5] == 0)
	{
		first_fork(philosopher, pthread_mutex_lock);
		if (philosopher->info[5] == -1
			&& first_fork(philosopher, pthread_mutex_unlock))
			break ;
		print("%ld %d has taken a fork\n", philosopher);
		second_fork(philosopher);
		gettimeofday(&tv, 0);
		philosopher->time_to_die = tv.tv_sec * 1000
			+ tv.tv_usec / 1000 + philosopher->info[1] - philosopher->info[6];
		if (philosopher->info[5] == -1 && unlock_all(philosopher))
			break ;
		eat_and_sleep(philosopher, &tv);
		if (philosopher->info[5] == -1)
			break ;
		print("%ld %d is thinking\n", philosopher);
	}
	return (0);
}
