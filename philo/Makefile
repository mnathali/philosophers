# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 22:42:04 by mnathali          #+#    #+#              #
#    Updated: 2022/04/15 22:29:33 by mnathali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = main.c libft.c lst_func.c solve_problem.c routine.c\
		philosophers_time.c

OBJS = $(patsubst %.c, %.o, $(SOURCES))

CC = cc

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c 
	$(CC) $(FLAGS) -c $<

$(OBJS): philos.h

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lpthread -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
