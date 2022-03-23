# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/26 13:32:52 by tor               #+#    #+#              #
#    Updated: 2022/03/23 16:06:57 by lnoirot          ###   ########.fr        #
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


PARSING_PATH	=	parsing/
UTILS_PATH	=	utils/

PARSING_LIST	=	$(addprefix $(PARSING_PATH), \
							parsing.c \
						)

UTILS_LIST	=	$(addprefix $(UTILS_PATH), \
							ft_atoi.c \
							ft_atoi_double.c \
							str_table_size.c \
						)

SRCS_LIST	=	main.c \
				$(PARSING_LIST) \
				$(UTILS_LIST)

SRCS			=	$(addprefix $(SRCS_PATH), \
						main.c \
						$(PARSING_LIST) \
						$(UTILS_LST) \
						)

OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS_LIST:.c=.o))

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
					@mkdir -p obj obj/parsing obj/utils
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

DEPS	=	$(OBJS:.o=.d)

all:	$(NAME)

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
