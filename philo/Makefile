# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 10:03:36 by idias-al          #+#    #+#              #
#    Updated: 2023/05/31 17:08:23 by idias-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS  =  ft_atoi.o main.o init_data.o
NAME = philo
CC = cc
CFLAGS = -g #-Wextra -Werror -Wall
GREEN           :=      \033[0;32m
RED             :=      \033[1;31m
WHITE           :=      \033[1;37m
BOLD            :=      \033[1;1ms
CYAN            :=      \033[0;36m

all : $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread
		@echo "$(GREEN) [Success] philo compilation.$(WHITE)"

clean:
		@rm -rf $(OBJS)
		@echo "$(CYAN) [cleaned] philo objects."

fclean: clean
		@rm -rf $(NAME)
		@echo "$(CYAN) [cleaned] philo executable.$(WHITE)"

re: fclean all

