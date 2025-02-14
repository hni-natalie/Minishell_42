# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 16:18:44 by hni-xuan          #+#    #+#              #
#    Updated: 2025/02/14 16:40:19 by rraja-az         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = '\033[0;33m'
RESET = '\033[0m'

CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
LFLAGS = -lreadline
RM = rm -rf

NAME = minishell

# Directories
LIBFT_DIR = ./libft
OBJ_DIR = ./obj/
MAIN_DIR = ./main/
PARSING_DIR = ./parsing/
HEREDOC_DIR = ./heredoc/
EXECUTION_DIR = ./execution/
BUILTIN_DIR = ./builtin/

# Files
MAIN_FILES = main signal
PARSING_FILES = token parsing init free arg_handler check 
HEREDOC_FILES = heredoc heredoc_utils
EXECUTION_FILES = execute setup
BUILTIN_FILES = builtin builtin_cd builtin_echo builtin_env builtin_env_utils builtin_exit builtin_export builtin_pwd builtin_unset 

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(MAIN_FILES)))
OBJ += $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSING_FILES)))
OBJ += $(addprefix $(OBJ_DIR), $(addsuffix .o, $(HEREDOC_FILES)))
OBJ += $(addprefix $(OBJ_DIR), $(addsuffix .o, $(EXECUTION_FILES)))
OBJ += $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BUILTIN_FILES)))

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@echo $(YELLOW) "----- 🔓 Unlocking Minishell 🔓 -----" $(RESET)
	@$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft $(LFLAGS)
	@echo $(YELLOW) "----- 🍌 Minishell is ready 🍌 -----" $(RESET)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(MAIN_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(HEREDOC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(EXECUTION_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@make -s -C $(LIBFT_DIR)

clean:
	@echo $(YELLOW) "----- 🧹 Cleaning Minishell 🧹 -----" $(RESET)
	@$(RM) $(OBJ_DIR)
	@make -s clean -C $(LIBFT_DIR)
	@echo $(YELLOW) "----- 👋 Done Bye 👋 -----" $(RESET)

fclean: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@make -s fclean -C $(LIBFT_DIR)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re