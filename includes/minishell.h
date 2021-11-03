/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:57:49 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 21:09:34 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** =============================================================================
** Dependencies
** =============================================================================
*/

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include "libft.h"

/*
** =============================================================================
** Macro Declaration
** =============================================================================
*/

# define TRUE 1
# define FALSE 0

# define ERROR -1
# define NORMAL 0

# define READ 0
# define WRITE 1

# define KEY 0
# define VALUE 1

# define FRONT 0
# define MID 1
# define BACK 2

# define BUF_SIZE 200000
# define ISODD 1

# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_NO_FILE_OR_DIR "No such file or directory"
# define MSG_IS_A_DIR "is a directory"

# define CODE_CMD_NOT_FOUND 127
# define CODE_NO_FILE_OR_DIR 127
# define CODE_IS_A_DIR 126

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef long long	t_ll;

/*
** =============================================================================
** Enum type Definition
** =============================================================================
*/

typedef enum e_type
{
	NORM = 0,
	SQUOTE,
	DQUOTE,
	SPCE,
	SPEC,
	DOLR,
	PIPE,
	END,
	RRDI,
	LRDI
}			t_type;

/*
** =============================================================================
** Union type Definition
** =============================================================================
*/

typedef union u_exit
{
	long long		num;
	unsigned char	c[8];
}			t_exit;

/*
** =============================================================================
** Struct type Definition
** =============================================================================
*/

typedef struct s_exit_code
{
	int	code;
	int	sig_flag;
}			t_exit_code;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				env_flag;
	struct s_env	*next;
	struct s_env	*prev;
}			t_env;

typedef struct s_env_deq
{
	int		size;
	t_env	*head;
	t_env	*last;
}			t_env_deq;

typedef struct s_pipex
{
	int		**pipe_fd;
	int		*pid;
	char	*limiter;
	int		is_here_doc;
	int		*here_fd;
	int		here_flag;
}	t_pipex;

typedef struct s_quote
{
	int	squote_flag;
	int	dquote_flag;
	int	squote_cnt;
	int	dquote_cnt;
}			t_quote;

typedef struct s_lst
{
	char			*str;
	struct s_lst	*next;
}			t_lst;

typedef struct s_cmd
{
	t_lst	*text;
	t_lst	*redi;
}			t_cmd;

typedef struct s_info
{
	char		**env_path;
	char		**cmd_str;
	int			cmd_sequence;
	int			here_sequence;
	int			n_cmd;
	int			last_pid;
	char		**env_str;
	char		*home_path;
	char		*pwd_path;
	t_env_deq	*env_deq;
	t_cmd		*cmd_lst;
	t_pipex		pipex;
}			t_info;

/*
** =============================================================================
** SOURCES / BUILTIN
** =============================================================================
*/

int		builtin(char **cmd, t_info *info, int *fd);
int		cd(char *path, t_info *info);
int		env(t_info *info, int *fd);
int		execute_exit(char **cmd, t_info *info);
int		export(char **cmd, t_info *info, int *fd);
void	print_export(t_info *info, int *fd);
int		pwd(int *fd, t_info *info);
int		unset(char **cmd, t_info *info);
int		echo(t_info *info, int *fd);

/*
** =============================================================================
** SOURCES / EXECUTE
** =============================================================================
*/

void	execute_command_main(t_info *info);
void	execute_command(t_info *info, int depth);
int		execute_execve(t_info *info);
int		is_builtin_command(t_info *info);

void	get_pipe_fd(t_info *info, int depth, int fd[]);
int		switch_stdio(t_info *info, int fd[]);
void	get_cmd_list(t_info *info);

void	init_pipe_fd(t_info *info);
void	make_pipeline(t_info *info, int depth);
void	close_pipeline(t_info *info);

void	fork_process(t_info *info, int depth);

int		wexitstatus(int status);

int		redirection(t_info *info, int fd[]);
int		here_doc(t_info *info, char *limiter);
void	is_here_doc(t_info *info, int depth);
int		run_here_doc(t_info *info);
int		get_here_doc_count(t_info *info);
void	init_here_fd(t_info *info);

/*
** =============================================================================
** SOURCES / FREE
** =============================================================================
*/

void	free_two_dimensional(char **two_dimensional);
void	free_double_string(char **list);
void	clear_info(t_info *info);

/*
** =============================================================================
** SOURCES / PARSE
** =============================================================================
*/

int		check_pipe_input(char **line);
char	*arrange_quote(char *line, int *start_idx, int sep_idx, t_info *info);
int		check_incorrect_line(char *line);
char	*fillin_buf(char *buf, char *origin, t_info *info);
char	*pre_processing(char *line, t_info *info);
void	make_command(char *line, t_info *info);
int		parse_line(char *line, t_info *info);

/*
** =============================================================================
** SOURCES / SIGNAL
** =============================================================================
*/

void	main_sig_handler(int signo);
void	pipe_input_handler(int signo);
void	here_doc_handler(int signo);
void	execve_handler(int signo);
void	newline_handler(int signo);

/*
** =============================================================================
** SOURCES / UTILITY
** =============================================================================
*/

int		ft_absol(int n);
int		check_sign(t_ll num);

t_env	*create_env_node(void);
void	link_env_node(t_env *front, t_env *back);
t_env	*make_env_list(char **envp);

char	**env_split(char *str);
t_env	*check_listin(char *env_key, t_info *info);
char	*get_env_value(char *key, t_info *info);
void	reset_env_path(t_info *info);
void	print_env_str(char **str, int *fd);
int		incorrect_env_key(char *env_key);
int		check_add_value(char **env);
void	reset_env_info(t_info *info);

void	merror(void *addr);
int		error_msg(char *cmd, char *arg, char *msg);
void	syntax_error(char *c);
void	unclosed_quote(char c);

t_lst	*create_node(void);
void	link_node(char *cmd, t_lst **list);

int		is_special(char c);
int		is_space(char c);
t_type	is_redirection(char c);
t_type	check_type(char c);
int		is_separator(char c);
void	init_quote_data(t_quote *data);
int		find_separator(char *line, int idx);
char	**quote_split(char *cmd);
char	choose_enclose_quote_type(char *buf, int buf_len);
void	turn_on_quote_flag(char c, t_quote *data);

int		is_register_variable_string(char *cmd);
int		is_register_variable(t_lst *text);
int		register_variable(char **cmd, t_info *info, int *fd);

void	make_env_double_string(t_info *info);
void	save_env_variables(t_info *info, char **envp);

int		double_string_size(char **str);
int		ft_strcmp(const char *s1, const char *s2);
void	swap_str(char **str, int i, int j);
void	sort_env_str(char **str);

void	set_environment_path(t_info *info);

#endif
