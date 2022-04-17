/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:35:28 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/15 16:18:51 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_list_chops	*create_new_mutex(int i, long *seconds, pthread_mutex_t *n)
{
	t_list_chops	*new;

	new = malloc(sizeof(t_list_chops));
	if (!new)
		return (0);
	new->n = n;
	new->next = 0;
	new->i = i;
	new->info = seconds;
	new->time_to_die = seconds[1];
	new->times_of_eat = seconds[4];
	if (pthread_mutex_init(&(new->m), 0) != 0)
		return (0);
	return (new);
}

void	ft_lstadd_front(t_list_chops **lst, t_list_chops *new)
{
	t_list_chops	*old;

	if (new)
	{
		old = *lst;
		*lst = new;
		new->next = old;
	}
}

void	lstclear(t_list_chops **lst)
{
	t_list_chops	*fre;

	while ((*lst) != 0)
	{
		fre = *lst;
		*lst = (*lst)->next;
		free(fre);
	}
}

t_list_chops	*ft_create_table(long *n, pthread_mutex_t *m)
{
	int				i;
	t_list_chops	*lst;
	t_list_chops	*new_elem;

	i = 0;
	lst = 0;
	new_elem = 0;
	while (i != *n)
	{
		new_elem = create_new_mutex(*n - i, n, m);
		if (!new_elem)
		{
			lstclear(&lst);
			return (0);
		}
		ft_lstadd_front(&lst, new_elem);
		i++;
	}
	new_elem = lst;
	while (new_elem->next)
		new_elem = new_elem->next;
	new_elem->next = lst;
	return (lst);
}
