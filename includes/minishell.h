/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:39:06 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:15:04 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <termios.h>

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

extern int g_exit;

typedef struct	s_err
{
	int				errcode;
	int				errindex;
	char			*errtoken;
}				t_err;

typedef struct	s_token
{
	char		*cmd;
	char		redir_flag;
}				t_token;

typedef struct	s_cmd
{
	t_token			*cmdline;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*(redirect_filename[4]);
	//index 0 : left redirect char (<, <<);
	//index 1 : left redirect filename;
	//index 2 : righ redirect char (>, >>);
	//index 3 : righ redirect filename;
	struct s_err	err_manage;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_split
{
	int	count;
	int begin;
	int	quote;
	int redirec;

}		t_split;

//main.c
t_cmd		*ft_new(char *line, int pipe, char **envp, int exit);
int			check_whitespace(char *line);

//signal.c
void	set_signal(void);
void	handler(int signum);

// parse.c
void	parse(t_cmd **cmd_list, char *line, char **envp);
void	add_new(t_cmd **cmd_list, t_cmd **new, t_cmd **tmp, int start);
void	check_pipe(char *line, int pipe, int i);
void	check_quote(char *line, int quote, int i);
void	init_flag(int *i, int *start, int *pipe, int *quote);

// env_create.c
char	**copy_envp(char **envs);
int		ft_env(char **envp, int fd);
int		has_equal(char *line);

//cmd_split.c
t_token	*cmd_split(char const *s, char c);
int		split_line(char const *s, const char c);
void	condition_count(t_split *info, char const *s, const char c, int *count);
void	get_count(int *redirec, int *count, int *begin, int begin_flag);
void	put_quote_flag(char const *s, int *quote);

//token_word.c
char	*token_word(int *idx, char const *s, const char c);
int		ft_word_len(char const *s, const char c);
int		conditoion_word_len(char const *s, const char c, int *len, t_split *info);
void	*ft_free(t_token *tokens, int len);

//set_token.c
t_token		*set_token(t_token *token, char **envp);
int		get_parse_size(char *str, char **envp);
int		double_quote_size(char *str, int *size, char **envp);
int		single_quote_size(char *str, int *size);
int		unclosed_quote(char *str, char quote);

//env_size.c
int		env_size(char *str, int *size, char **envp);
int		env_key_size(char *str);
int		env_value_size(char *str, int size, char **envp);


#endif
