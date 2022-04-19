/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_time.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 22:28:30 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/15 22:28:46 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

char	check_times_of_eat(t_list_chops	*philosopher)
{
	int	i;

	i = 0;
	while (i != philosopher->info[0])
	{
		if (philosopher->times_of_eat != 0)
			return (0);
		i++;
		philosopher = philosopher->next;
	}
	return (1);
}

char	everybodys_time(struct timeval *tv, t_list_chops **data)
{
	short			i;
	t_list_chops	*philosopher;

	i = 0;
	philosopher = *data;
	gettimeofday(tv, 0);
	while (i != philosopher->info[0])
	{
		if (tv->tv_sec * 1000 + tv->tv_usec / 1000
			- philosopher->info[6] > philosopher->time_to_die)
		{
			*data = philosopher;
			return (1);
		}
		philosopher = philosopher->next;
		i++;
	}
	return (0);
}

void	*philosophers_time(void *data)
{
	t_list_chops	*philosopher;
	struct timeval	tv;

	philosopher = (t_list_chops *)data;
	while (philosopher->info[5] == 1)
		my_sleep(1);
	while (philosopher->info[5] != -1)
	{
		if (philosopher->time_to_die > 0 && everybodys_time(&tv, &philosopher))
		{
			philosopher->info[5] = -1;
			if (print("%ld %d died\n", philosopher) && philosopher->info[0] == 1)
				pthread_mutex_unlock(&philosopher->m);
			break ;
		}
		if (philosopher->times_of_eat == 0 && check_times_of_eat(philosopher))
		{
			philosopher->info[5] = -1;
			break ;
		}
		my_sleep(1000);
	}
	return (0);
}
