# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tor <tor@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/26 13:32:52 by tor               #+#    #+#              #
#    Updated: 2021/12/26 13:59:12 by tor              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES	:

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -MMD -g3
RM		=	rm -rf

INC_PATH	=	./inc
INCLUDES	=	-I$(INC_PATH)

OBJ_PATH	=	obj/

SRCS_PATH 		=	srcs/

SRCS			= main.c

OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

DEPS	=	$(OBJS:.o=.d)

all:
			@mkdir -p obj
			$(MAKE) ${NAME}

${NAME}:	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)
		@echo "philo is compiled"

clean:	
		$(RM) $(OBJS)
		$(RM) $(DEPS)
		@echo "Cleaned .o !"

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(OBJ_PATH)
			$(RM) $(DEPS)
			@echo "All cleaned !"

vg:			$(NAME)
			valgrind --track-origins=yes ./philo

re:			fclean all

run:		$(NAME)
			./philo

.PHONY : all clean run vg

-include $(DEPS)
