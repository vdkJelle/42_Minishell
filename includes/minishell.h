/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 10:33:33 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/18 19:09:24 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define READ 0
# define WRITE 1
# define NO_REDIRECTION -2

/*
**------------------------------GLOBAL VARIABLES--------------------------------
*/

/*
**------------------------------------ENUMS-------------------------------------
*/

typedef 		enum
{
				NON_BUILTIN = -1,
				CD = 0,
				ECHO = 1,
				ENV = 2,
				EXIT = 3,
				EXPORT = 4,
				PWD = 5,
				UNSET = 6,
}				e_command;

typedef			enum
{
				ERROR = -1,
				REGULAR = 0,
				BIN = 1,
				USR_BIN = 2,
				DIRECTORY = 3,
				NOT_FOUND = 4,
				NOT_EXECUTABLE = 5,
}				e_file;

typedef 		enum
{
				CHAR = 0,
				DOUBLEQUOTE = 1,
				ENVIRONMENT_VARIABLE = 2,
				METACHARACTER = 3,
				SINGLEQUOTE = 4,
				BACKSLASH = 5,
}				arg_characters;



/*
**-----------------------------------STRUCTS------------------------------------
*/

typedef struct	s_exec
{
	char		**args;
	char		*path;
	int			fd[2];
	int			p_fd[2];
	int			piped;
}				t_execute;

typedef struct	s_word
{
	t_list		*word_segment;
	char		*word;
	int			metacharacter;
}				t_word;

typedef struct	s_token
{
	t_word		*cmd;
	t_word		**arg;
	char		*cop;
}				t_token;

typedef struct	s_data
{
	char		**args;
	char		**our_env;
	char		*input;
	int			env_size;
	int			our_fd[2];
	int			r;
	int			exit_status;
	t_list		*token;
}				t_data;

/*
**----------------------------POINTERS TO FUNCTIONS-----------------------------
*/
typedef int		(*f_arg_handler)(t_data *data, t_word **word, char *s);
typedef void	(*f_builtin)(t_data *data);

/*
**-----------------------------------ENV.C--------------------------------------
*/
void	ft_env(t_data *data);

/*
**---------------------------------EXPORT.C-------------------------------------
*/
void	append_key_value(char *arg, char ***our_env, int *env_size);
void	ft_export(t_data *data);

/*
**----------------------------------FT_CD.C-------------------------------------
*/
void	ft_cd(t_data *data);

/*
**---------------------------------FT_ECHO.C------------------------------------
*/
void	ft_echo(t_data *data);

/*
**---------------------------------FT_EXIT.C------------------------------------
*/
void	ft_exit(t_data *data);

/*
**---------------------------------FT_PWD.C-------------------------------------
*/
void	ft_pwd(t_data *data);

/*
**---------------------------------GET_ENV.C------------------------------------
*/
char	*get_env(char **env, char *key);

/*
**-----------------------------HANDLE_ARG_CHARS.C-------------------------------
*/
int		handle_char(t_data *data, t_word **word, char *s);
int		handle_doublequotes(t_data *data, t_word **word, char *s);
int		handle_environment_variable(t_data *d, t_word **word, char *s);
int		handle_metacharacter(t_data *data, t_word **word, char *s);
int		handle_singlequotes(t_data *data, t_word **word, char *s);

/*
**----------------------------------MAIN.C--------------------------------------
*/
int		main(void);

/*
**--------------------------------REDIRECTION.C---------------------------------
*/
int		redirection(t_data *data, t_word **arg, int i, int fd[2]);

/*
**--------------------------------TOKEN_ARG.C-----------------------------------
*/
int		get_arg(t_data *data, t_word **word, char *s, char control_op);

/*
**-------------------------------TOKEN_CHECK.C----------------------------------
*/
int		check_token(t_data *data);

/*
**----------------------------------TOKEN.C-------------------------------------
*/
void	get_token(t_data *data, char *s);

/*
**------------------------------------UNSET-------------------------------------
*/
void	ft_unset(t_data *data);

/*
**--------------------------------UTILS_LIST.C----------------------------------
*/
void	free_array(char **array);
void	free_array_part(char **array, int i);
void	free_exec(t_execute *exec);
void	free_token(void *content);
char	*join_word(t_word *arg);
void 	print_token(void *content);

/*
**-----------------------------UTILS_STRING_SKIP.C-------------------------------
*/
int		skip_until_next_doubleq(char *s);
int		skip_until_next_singleq(char *s);
int		skip_until_char_excl(char *s, char c);
int		skip_until_char_incl(char *s, char c);
int		skip_while_char(char *s, int (*ft_isthis)(char c));
int		skip_while_not_char(char *s, int (*ft_isthis)(char c));
// int		skip_until_f_int(char *s, int (*ft_isthis)(int c));
// int		skip_until_metacharacter_incl(char *s);
// int		skip_chars_int(char *s, char c);
// int		skip_metacharacters_int(char *s);
// int		skip_nonwhitespaces_int(char *s);
// int		skip_whitespaces_int(char *s);
// int		skip_until_metacharacterexcl(char *s);
// void	skip_char(char **s, char c);
// void	skip_chars(char **s, char c);
// void	skip_whitespaces(char **s);
// void	skip_nonwhitespaces(char **s);

/*
**-----------------------------UTILS_STRING_COUNT.C------------------------------
*/
int		count_arguments(char *s, char c);
int		count_backslash(char *s, int loc);
// int		count_words(char const *s, char c);

/*
**-------------------------------UTILS_STRING.C---------------------------------
*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_wrapper(char *s1, char *s2, int mode);
// char	*put_in_singlequotes(char *s);

/*
**--------------------------UTILS_STRING_STRJOIN.C------------------------------
*/
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char const *s2);

/*
**----------------------------UTILS_STRING_IS_THIS.C----------------------------
*/
int		is_control_operator(char s);
int		is_metacharacter(char c);
int		is_redirection(char *s);
int		is_whitespace(char c);

e_file	check_file(t_data *data, char *s);
// int		execute(t_data *data, t_execute *cur, t_execute *prev);

void	print_errno(void);
int		print_errno_int(void);
void	print_error(t_data *data, int exit_status, int n, ...);
// void	print_error_message(t_data *data, int exit_status, char *s1, char *s2);

void	signal_output(int sig);
void	ft_signal_handler(void);

int		check_multiline_command(t_data *data, char *s);

void	final_args(t_data *data, t_token *token, t_execute *exec);

void	execute_builtin_pipe(t_data *data, e_command cmd, t_execute *exec);
void	execute_builtin_no_pipe(t_data *data, e_command cmd, t_execute *exec);

void	create_process(t_data *data, e_command cmd, t_execute *cur, t_execute *prev);

void	cody_catch(t_data *data);

#endif
