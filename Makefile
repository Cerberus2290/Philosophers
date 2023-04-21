# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 10:28:44 by tstrassb          #+#    #+#              #
#    Updated: 2023/04/21 12:15:14 by tstrassb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CFLAGS		=	-g -pthread -Wall -Wextra -Werror

RM			=	rm -rf

SRCS		=	$(SRC_MAIN)

MAIN		=	init.c main.c philo_acts.c philo_control.c timeutils.c utils.c
SRC_MAIN	=	$(addprefix src/, $(MAIN))

OBJ			=	*.o

#colors
DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

all:			$(NAME)
				@echo "$(YELLOW)---------------------------------------------"
				@echo "|                                           |"
				@echo "|               Philosophers                |"
				@echo "|                                           |"
				@echo "|         keep the smart and wise           |"
				@echo "|        alive as long as possible          |"
				@echo "|                                           |"
				@echo "---------------------------------------------$(DEF_COLOR)"
				@say "Philosophers, keep the smart and wise alive as long as possible"
				@echo "$(CYAN)********************************************"
				@echo "*          To check Norminette             *"
				@echo "*            type: $(WHITE)make norm$(CYAN)               *"
				@echo "********************************************$(DEF_COLOR)"

$(NAME):		$(OBJ)
					@echo "$(GREEN)-compiling philo...$(DEF_COLOR)"
					@cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ):			$(SRCS)
					@echo "$(BLUE)-creating object files...$(DEF_COLOR)"
					@cc $(CFLAGS) -c $(SRCS)

norm:
					@echo "$(RED)Checking the Norm..."
					@echo "$(GREEN)"
					@sleep 1.5
					@norminette inc/ src/
					@echo "$(DEF_COLOR)"

clean:
					@echo "$(YELLOW)-Cleaning object files...$(DEF_COLOR)"
					@$(RM) *.o
					@echo "$(GREEN)---CLEANED!---$(DEF_COLOR)"
					@say "Cleaned!"

fclean:			clean
					@echo "$(YELLOW)-Cleaning remaining files...$(DEF_COLOR)"
					@$(RM) $(NAME)
					@echo "$(GREEN)---CLEANED!---$(DEF_COLOR)"
					@say "Cleaned!"

re:				fclean all