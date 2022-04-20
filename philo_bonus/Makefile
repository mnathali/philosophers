# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 22:42:04 by mnathali          #+#    #+#              #
#    Updated: 2022/04/20 21:51:28 by mnathali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SOURCES = main_bonus.c libft_func_bonus.c ft_solve_problem_bonus.c\
			ft_routine_bonus.c

OBJS = $(patsubst %.c, %.o, $(SOURCES))

CC = cc

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c 
	$(CC) $(FLAGS) -c $<

$(OBJS): philos_bonus.h

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lpthread -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
