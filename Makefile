# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 20:16:04 by kyunkim           #+#    #+#              #
#    Updated: 2021/11/03 21:21:13 by hyeonkki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Color Variables
# =============================================================================

BLACK		= 	"\033[0;30m"
GRAY		= 	"\033[1;30m"
RED			=	"\033[1;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[0;35m"
CYAN		=	"\033[1;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

# =============================================================================
# Command Variables
# =============================================================================

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g
READ_INC_FG	=	-I$(HOME)/.brew/opt/readline/include
READ_LIB_FG	=	-L$(HOME)/.brew/opt/readline/lib
RM			=	rm -rf

# =============================================================================
# File Variables
# =============================================================================

NAME		=	minishell

INC			=	./includes/
LIBFT		=	./Libft/
SRCS_DIR	=	./srcs/
OBJS_DIR	=	./objs/

MAIN_DIR	=	main/
BLTIN_DIR	=	builtin/
ENV_DIR		=	env/
EXEC_DIR	=	execute/
FREE_DIR	=	free/
PARSE_DIR	=	parse/
SIG_DIR		=	signal/
UTL_DIR		=	utility/

OBJS_LST	=	main.o						\
				builtin.o					\
				cd.o						\
				env.o						\
				exit.o						\
				export.o					\
				print_export.o				\
				free.o						\
				pwd.o						\
				unset.o						\
				echo.o						\
				save_env_values.o			\
				execute_cmd.o				\
				execute_execve.o			\
				get_cmd_list.o				\
				make_pipeline.o				\
				close_pipeline.o			\
				fork_process.o				\
				get_pipe_fd.o				\
				redirection.o				\
				here_doc.o					\
				switch_stdio.o				\
				wexitstatus.o				\
				free_two_dimensional.o		\
				arrange_quote.o				\
				check_incorrect_line.o		\
				check_pipe_input.o			\
				fillin_buffer.o				\
				make_command.o				\
				parse.o						\
				pre_processing_line.o		\
				signal.o					\
				builtin_utils.o				\
				error.o						\
				env_list.o					\
				env_utils.o					\
				env_utils2.o				\
				list.o						\
				string_utils.o				\
				parse_utils.o				\
				parse_utils2.o				\
				parse_utils3.o				\
				register_variable.o

OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

# =============================================================================
# Target Generating
# =============================================================================

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(MAIN_DIR)%.c
					@make all -C $(LIBFT)
					@mkdir -p $(OBJS_DIR)
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(BLTIN_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(ENV_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(EXEC_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(FREE_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(PARSE_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(SIG_DIR)%.c
					@$(CC) $(CFLAGS) $(READ_INC_FG) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)$(UTL_DIR)%.c
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
					@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)

$(NAME)			:	$(OBJS)
					@echo $(GREEN) "Source files are compiled!\n" $(EOC)
					@echo $(WHITE) "Building '$(NAME)' for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
					@$(CC) $(CFLAGS) $(READ_INC_FG) $(READ_LIB_FG) -lreadline -o $@ $^ $(LIBFT)libft.a -I$(INC)
					@echo $(CYAN) "'$(NAME)'(execute file) is created!\n" $(EOC)

# =============================================================================
# Rules
# =============================================================================

all				:	$(NAME)

clean			:
					@$(RM) $(OBJS_DIR)
					@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean			:	clean
					@make fclean -C $(LIBFT)
					@$(RM) $(NAME)
					@echo $(RED) "Execute file is removed!\n" $(EOC)

re				:
					make fclean
					make all

.PHONY			:	clean fclean re all bonus
