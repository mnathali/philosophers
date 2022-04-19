/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:53:48 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/18 02:18:31 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	*philosophers_time(void *gather)
{
	struct timeval	tv;
	t_list_chops	*data;
	short			i;

	data = (t_list_chops *)gather;
	i = data->info[0];
	while (data->info[5] != -1)
	{
		gettimeofday(&tv, 0);
		if (data->info[6] > 0 && tv.tv_sec * 1000 + tv.tv_usec / 1000
			- data->info[6] > data->info[5])
		{
			data->info[5] = -1;
			if (data->info[0] == 1)
				sem_post(data->semaphore[0]);
			sem_wait(data->semaphore[2]);
			while (i--)
				sem_post(data->semaphore[3]);
			print("%ld %d died\n", data);
			sem_post(data->semaphore[2]);
			break ;
		}
		my_sleep(1000);
	}
	return (0);
}

void	take_forks(t_list_chops	*philosopher)
{
	sem_wait(philosopher->semaphore[2]);
	sem_wait(philosopher->semaphore[0]);
	sem_wait(philosopher->semaphore[0]);
	sem_post(philosopher->semaphore[2]);
	return ;
}

void	cut_this_func(t_list_chops *philosopher)
{
	print("%ld %d has taken a fork\n", philosopher);
	print("%ld %d has taken a fork\n", philosopher);
	if (philosopher->info[5] == -1)
		return ;
	print("%ld %d is eating\n", philosopher);
	my_sleep(philosopher->info[2]);
	if (philosopher->info[5] == -1)
		return ;
	philosopher->info[4]--;
	if (philosopher->info[4] == 0)
		sem_post(philosopher->semaphore[3]);
	sem_post(philosopher->semaphore[0]);
	sem_post(philosopher->semaphore[0]);
	print("%ld %d is sleeping\n", philosopher);
	my_sleep(philosopher->info[3]);
	if (philosopher->info[5] == -1)
		return ;
	print("%ld %d is thinking\n", philosopher);
	return ;
}

void	*philosophers_routine(void *data)
{
	struct timeval	tv;
	t_list_chops	*philosopher;

	philosopher = (t_list_chops *)data;
	sem_wait(philosopher->semaphore[5]);
	gettimeofday(&tv, 0);
	philosopher->info[6] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (philosopher->info[5] != -1)
	{
		take_forks(philosopher);
		gettimeofday(&tv, 0);
		if (philosopher->info[5] != -1)
			philosopher->info[5] = philosopher->info[1] + tv.tv_sec * 1000
				+ tv.tv_usec / 1000 - philosopher->info[6];
		else
		{
			sem_post(philosopher->semaphore[0]);
			sem_post(philosopher->semaphore[0]);
			break ;
		}
		cut_this_func(philosopher);
	}
	return (0);
}
