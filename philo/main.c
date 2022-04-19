/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:22:10 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/15 17:47:48 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	my_sleep(int n)
{
	struct timeval	tv;
	long			i;

	gettimeofday(&tv, 0);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (i + n / 1000 > tv.tv_sec * 1000 + tv.tv_usec / 1000)
	{
		gettimeofday(&tv, 0);
		usleep(10);
	}
}

void	ft_cleardata(t_list_chops **lst, pthread_t **t, long i)
{
	t_list_chops	*fre;

	while (i > 0 && *lst)
	{
		fre = *lst;
		*lst = (*lst)->next;
		free(fre);
		i--;
	}
	if (t[0])
		free(t[0]);
	if (t[1])
		free(t[1]);
	return ;
}

char	print(char *str, t_list_chops *philosopher)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	pthread_mutex_lock(philosopher->n);
	printf(str, tv.tv_sec * 1000 + tv.tv_usec / 1000 - philosopher->info[6],
		philosopher->i);
	pthread_mutex_unlock(philosopher->n);
	return (1);
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

int	main(int argc, char const *argv[])
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
	{
		ft_solve_problem(argv, 0);
		return (0);
	}
	if (argc < 5 || argc > 6)
		printf("Error: number of parameters can be 4 or 5.\n");
	else if (ft_atoi_long(argv[1]) >= 1000 || ft_atoi_long(argv[1]) == 0)
		printf("Error: max number of philosophers = 999, min = 1.\n");
	else if (argc == 6 && ft_atoi_long(argv[5]) >= 50000)
		printf("Error: max number of times they sould eat = 49999.\n");
	return (1);
}
