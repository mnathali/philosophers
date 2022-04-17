/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_problem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:04:35 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/15 22:28:23 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

short	read_args(long *info, const char **argv, pthread_t **t,
	pthread_mutex_t *n)
{
	if (pthread_mutex_init(n, 0) != 0)
		return (1);
	info[0] = ft_atoi_long(argv[1]);
	info[1] = ft_atoi_long(argv[2]);
	info[2] = ft_atoi_long(argv[3]) * 1000;
	info[3] = ft_atoi_long(argv[4]) * 1000;
	if (argv[5])
		info[4] = ft_atoi_long(argv[5]);
	else
		info[4] = 50000;
	info[5] = 1;
	t[0] = malloc(info[0] * sizeof(pthread_t));
	t[1] = malloc(sizeof(pthread_t));
	return (0);
}

void	start_time(long *info)
{
	struct timeval	tv;

	usleep(info[0] * 10000);
	gettimeofday(&tv, 0);
	info[6] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	info[5] = 0;
}

void	ft_solve_problem(const char **argv, int i)
{
	pthread_t		*t[2];
	t_list_chops	*forks;
	long			info[7];
	pthread_mutex_t	n;

	if (read_args(&info[0], argv, &t[0], &n))
		return ;
	forks = ft_create_table(&info[0], &n);
	if (pthread_create(&t[1][i], 0, philosophers_time, forks))
		info[5] = -1;
	while (info[5] != -1 && t[0] && t[1] && forks && i != info[0])
	{
		if (pthread_create(&t[0][i], 0, philosophers_routine, forks))
			info[5] = -1;
		i++;
		forks = forks->next;
	}
	start_time(&info[0]);
	pthread_join(t[1][0], 0);
	while (t[0] && t[1] && forks && i != 0)
	{
		i--;
		pthread_join(t[0][i], 0);
	}
	ft_cleardata(&forks, &t[0], info[0]);
}
