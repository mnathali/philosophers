/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:19:56 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/18 02:17:27 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ipc.h>
# include <pthread.h>

typedef struct s_list_chops
{
	int		i;
	long	*info;
	sem_t	**semaphore;
}	t_list_chops;

long	ft_atoi_long(const char *str);
int		ft_isdigit(int i);
size_t	ft_strlen(const char *str);
void	ft_solve_problem(const char **argv);
void	*philosophers_routine(void *data);
void	*philosophers_time(void *gather);
char	print(char *str, t_list_chops *philosopher);
void	my_sleep(int n);

#endif