# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/26 13:32:52 by tor               #+#    #+#              #
#    Updated: 2022/03/25 20:38:56 by lnoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES	:

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MMD -g3
RM		=	rm -rf

INC_PATH	=	./inc
INCLUDES	=	-I$(INC_PATH)

OBJ_PATH	=	obj/

SRCS_PATH 		=	srcs


PARSING_PATH	=	parsing/
UTILS_PATH	=	utils/
THREADS_PATH	=	threads/
DISPLAY_PATH	=	display/

PARSING_LIST	=	$(addprefix $(PARSING_PATH), \
							parsing.c \
						)

UTILS_LIST	=	$(addprefix $(UTILS_PATH), \
							ft_atoi.c \
							ft_atoi_long.c \
							str_table_size.c \
							ft_itoa.c \
							ft_strdup.c \
							ft_strlen.c \
						)

THREADS_LIST	=	$(addprefix $(THREADS_PATH), \
							create_fork_threads.c \
							create_philo_threads.c \
							activity.c \
							time.c \
							check_death.c \
							nb_meal.c \
						)

DISPLAY_LIST	=	$(addprefix $(DISPLAY_PATH), \
							access_display.c \
							print_state_change.c \
						)

SRCS_LIST	=	main.c \
				$(PARSING_LIST) \
				$(UTILS_LIST) \
				$(THREADS_LIST) \
				$(DISPLAY_LIST)

SRCS			=	$(addprefix $(SRCS_PATH), \
						main.c \
						$(PARSING_LIST) \
						$(UTILS_LST) \
						$(THREADS_LIST) \
						$(DISPLAY_LIST) \
						)

OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS_LIST:.c=.o))

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
					@mkdir -p obj obj/parsing obj/utils obj/threads obj/display
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

DEPS	=	$(OBJS:.o=.d)

all:	$(NAME)

${NAME}:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
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
