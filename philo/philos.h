/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:19:56 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/15 22:29:05 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_list_chops
{
	pthread_mutex_t		m;
	pthread_mutex_t		*n;
	int					i;
	long				*info;
	long				time_to_die;
	unsigned short		times_of_eat;
	struct s_list_chops	*next;
}	t_list_chops;

long			ft_atoi_long(const char *str);
int				ft_isdigit(int i);
size_t			ft_strlen(const char *str);
t_list_chops	*ft_create_table(long *n, pthread_mutex_t *m);
void			ft_lstadd_front(t_list_chops **lst, t_list_chops *new);
t_list_chops	*create_new_mutex(int i, long *seconds, pthread_mutex_t *n);
void			ft_solve_problem(const char **argv, int i);
void			*philosophers_routine(void *data);
void			*philosophers_time(void *data);
char			print(char *str, t_list_chops *philosopher);
void			ft_cleardata(t_list_chops **lst, pthread_t **t, long i);
char			everybodys_time(struct timeval *tv, t_list_chops *philosopher);

#endif
