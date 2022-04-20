/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:22:10 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/20 15:26:40 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	my_sleep(int n)
{
	struct timeval	tv;
	long			i;

	gettimeofday(&tv, 0);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (i + n > tv.tv_sec * 1000 + tv.tv_usec / 1000)
	{
		gettimeofday(&tv, 0);
		usleep(10);
	}
}

short	check_args(const char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 11)
	{
		printf("Error: Too long arg.\n");
		return (1);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("Error: Args should be positive numbers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

short	check_input(int argc, char const **argv)
{
	int	i;

	i = 0;
	while ((argc == 5 || argc == 6) && argc - 1 - i > 0)
	{
		if (check_args(argv[argc - 1 - i]))
			return (1);
		i++;
	}
	if ((argc == 5 || (argc == 6 && ft_atoi_long(argv[5]) < 50000))
		&& argc > 1 && ft_atoi_long(argv[1]) < 1000
		&& ft_atoi_long(argv[1]) > 0)
		return (0);
	if (argc < 5 || argc > 6)
		printf("Error: number of parameters can be 4 or 5.\n");
	else if (ft_atoi_long(argv[1]) >= 1000 || ft_atoi_long(argv[1]) == 0)
		printf("Error: max number of philosophers = 999, min = 1.\n");
	else if (argc == 6 && ft_atoi_long(argv[5]) >= 50000)
		printf("Error: max number of times they sould eat = 49999.\n");
	return (1);
}

char	print(char *str, t_list_chops *philosopher)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	sem_wait(philosopher->semaphore[1]);
	printf(str, tv.tv_sec * 1000 + tv.tv_usec / 1000 - philosopher->info[6],
		philosopher->i);
	sem_post(philosopher->semaphore[1]);
	return (1);
}

int	main(int argc, char const *argv[])
{
	if (check_input(argc, argv))
		return (1);
	ft_solve_problem(argv);
	return (0);
}
