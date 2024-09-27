# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seyun <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 16:49:41 by seyun             #+#    #+#              #
#    Updated: 2022/03/02 02:06:31 by eyoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Color Variables
# =============================================================================

BLACK		= 	"\033[0;30m"
GRAY		= 	"\033[1;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

# =============================================================================
# Command Variables
# =============================================================================

NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra #-g3 -fsanitize=address
RM			=	rm -f

HEADER		=	./includes/
LIBFT_A		= 	./Libft/libft.a
LIBFT_D		=	./Libft/
RL			=   readline 
RLL			=	/Users/$(USER)/.brew/opt/readline/lib 
RLI			= 	/Users/$(USER)/.brew/opt/readline/include
#RLL			=	/Users/$(USER)/homebrew/opt/readline/lib 
#RLI			= 	/Users/$(USER)/homebrew/opt/readline/include


# =============================================================================
# File Variables
# =============================================================================

FILES 	=	main.c \
			env_create.c \
			parse.c \
			signal.c \
			cmd_split.c\
			token_word.c\
			set_token.c\
			env_size.c\

SRC		=   $(addprefix srcs/, $(FILES))
OBJ		=	$(SRC:.c=.o)
INCLIB	=	-Llibft -lft

# =============================================================================
# Target Generating
# =============================================================================

all			:	$(NAME)

%.o			:	%.c
				@make -C $(LIBFT_D)
				@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
				@$(CC) $(CFLAGS) -I $(HEADER) -I $(LIBFT_D) -I $(RLI) -o $@ -c $<

$(NAME)		:	$(OBJ)
				@echo $(GREEN) "Source files are compiled!\n" $(EOC)
				@echo $(WHITE) "Building $(NAME) for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLIB) -l$(RL) -L $(RLL)
				@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

# =============================================================================
# Rules
# =============================================================================

clean		:
				@echo $(YELLOW) "Cleaning object files..." $(EOC)
				@$(RM) $(OBJ)
				@make -C $(LIBFT_D) clean
				@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean		:	clean
				@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
				@$(RM) $(NAME)
				@rm -f $(NAME) $(LIBFT_A)
				@echo $(RED) "$(NAME) is removed!\n" $(EOC)

re			:	fclean all

.PHONY		:	norm
norm		:
				@norminette
