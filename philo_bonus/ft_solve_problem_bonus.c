/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_problem_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:37:53 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/20 21:49:38 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	ft_your_child(int i, long *info, sem_t **semen)
{
	pthread_t		t_1;
	t_list_chops	data;
	pthread_t		t_2;

	data.i = i;
	data.info = info;
	data.semaphore = semen;
	if (pthread_create(&t_1, 0, philosophers_time, &data)
		|| pthread_create(&t_2, 0, philosophers_routine, &data))
	{
		while (info[0]--)
			sem_post(data.semaphore[3]);
	}
	sem_wait(semen[4]);
	data.info[5] = -1;
	pthread_join(t_1, 0);
	pthread_join(t_2, 0);
	return ;
}

void	read_args(long *info, const char **argv, int *i)
{
	info[0] = ft_atoi_long(argv[1]);
	info[1] = ft_atoi_long(argv[2]);
	info[2] = ft_atoi_long(argv[3]);
	info[3] = ft_atoi_long(argv[4]);
	if (argv[5])
		info[4] = ft_atoi_long(argv[5]);
	else
		info[4] = 50000;
	info[5] = info[1];
	info[6] = 0;
	*i = 0;
	return ;
}

void	initialize_sem(unsigned int i, sem_t **semaphore)
{
	sem_unlink("forks");
	sem_unlink("let_print");
	sem_unlink("let_take");
	sem_unlink("exit_parent");
	sem_unlink("exit_child");
	sem_unlink("wait_children");
	sem_unlink("dead");
	semaphore[0] = sem_open("forks", O_CREAT, 0660, i);
	semaphore[1] = sem_open("let_print", O_CREAT, 0660, 1);
	semaphore[2] = sem_open("let_take", O_CREAT, 0660, 1);
	semaphore[3] = sem_open("exit_parent", O_CREAT, 0660, 0);
	semaphore[4] = sem_open("exit_child", O_CREAT, 0660, 0);
	semaphore[5] = sem_open("wait_children", O_CREAT, 0660, 0);
	semaphore[6] = sem_open("dead", O_CREAT, 0660, 1);
	return ;
}

void	ft_you_father(sem_t **semaphore, int i, long info)
{
	my_sleep(10 * info);
	while (i)
	{
		sem_post(semaphore[5]);
		i--;
	}
	while (i != info)
	{
		sem_wait(semaphore[3]);
		i++;
	}
	while (i)
	{
		sem_post(semaphore[4]);
		i--;
	}
	while (i != info)
	{
		waitpid(0, 0, 0);
		i++;
	}
}

void	ft_solve_problem(const char **argv)
{
	sem_t	*semaphore[8];
	int		pid;
	int		i;
	long	info[7];

	read_args(&info[0], argv, &i);
	initialize_sem(info[0], &semaphore[0]);
	while (i != info[0])
	{
		pid = fork();
		if (pid == 0)
			break ;
		i++;
	}
	if (pid == 0)
		ft_your_child(i + 1, &info[0], &semaphore[0]);
	else
		ft_you_father(&semaphore[0], i, info[0]);
	sem_close(semaphore[0]);
	sem_close(semaphore[1]);
	sem_close(semaphore[2]);
	sem_close(semaphore[3]);
	sem_close(semaphore[4]);
	sem_close(semaphore[5]);
	sem_close(semaphore[6]);
}
