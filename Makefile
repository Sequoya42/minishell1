#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 15:34:34 by rbaum             #+#    #+#              #
#    Updated: 2015/02/13 15:10:42 by rbaum            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY:			all, libft, clean, fclean, re

CC =			gcc

CFLAG =			-Wall -Werror -Wextra

NAME =			ft_minishell1

SRC_PATH =		./src/

OBJ_PATH =		./obj/

LIBFT_PATH =	./libft/

INC_PATH =		./inc/

SRC_NAME =		main.c\
				ft_prompt.c\
				ft_gest_cmd.c\
				ft_env.c\
				ft_short_cmd.c\

OBJ_NAME =		$(SRC_NAME:.c=.o)

LIBFT_NAME =	libft.a

INC_NAME =		ft_sh1.h

SRC =			$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ =			$(addprefix $(OBJ_PATH),$(OBJ_NAME))

LIBFT =			$(addprefix $(LIBFT_PATH),$(LIBFT_NAME))

INC =			$(addprefix $(INC_PATH),$(INC_NAME))

INCLIBFT_PATH =	$(LIBFT_PATH)

all:			libft $(NAME)

$(NAME):		$(OBJ)
				@$(CC) -L$(LIBFT_PATH) -lft -o $(NAME) $(OBJ)
				@echo "minishell created"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAG) -I$(INC_PATH) -I$(INCLIBFT_PATH) -o $@ -c $<

libft:			$(LIBFT)

$(LIBFT):
				@make -C $(LIBFT_PATH)

clean:
				@make -C $(LIBFT_PATH) clean
				@rm -f $(OBJ)

fclean:			
				@rm -f $(OBJ)
				@make -C $(LIBFT_PATH) fclean
				@rm -f $(NAME)

re: 			fclean all