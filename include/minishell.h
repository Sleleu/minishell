/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/12 15:03:22 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/* ********************************************************** */
/*                           INIT                             */
/* ********************************************************** */

t_data			*get_data(void);
t_data			*set_data(char **env);
void			restore_data(void);

/* ********************************************************** */
/*                          BUILTIN                           */
/* ********************************************************** */

int				ft_pwd(void);
int				ft_env(char **env);
int				ft_echo(char **arg);
int				ft_unset(t_data **data, char **cmd);

/* CD */

char			*ft_getenv(char **env, char *str);
int				ft_cd(char **arg, char **env);

/* EXPORT */

int				export_error_num(char **cmd);
int				ft_export_check_arg(t_data **data, t_parse *parse);
void			ft_refresh_var(t_data **data, char *str, int index_equal);
void			ft_export_action(t_data **data, char *str, int index_equal);
int				ft_export(t_data **data, char **cmd);

/* EXPORT_IS_VAR */

int				is_env_variable(char *str, int *code);
int				isalnum_var(char *str, int index_equal);
int				is_new_var(char **env, char *str);

/* EXPORT UTILS */

char			**ft_envjoin(char **env, char *str);
char			*ft_strdel(char *str, char c, int n);
char			**ft_append_var(char **env, char *str, int index_equal);

/* EXIT */

long long int	ft_long_atoi(char *str);
int				exit_numeric_error(t_data **data, char *str);
int				exit_error(t_data **data, char **cmd);
void			ft_exit(t_data **data, char **cmd);

/* ********************************************************** */
/*                          MEMCENTER                         */
/* ********************************************************** */

void			*memcenter(t_mem mem, size_t size, void *adress, t_label label);
void			*mempurge(t_memcenter *head);
void			*memfree(t_memcenter *head, void *adress);
void			*memfreewhere(t_memcenter *head, t_label label);
void			*first_malloc(size_t size, void *adress, t_label label);
void			*after_malloc(size_t size, void *adress, t_label label);

/* ********************************************************** */
/*                           LEXER                            */
/* ********************************************************** */

t_lexer			*ft_lexer(char *line);
int				select_chevron(t_lexer **token, char *line, int pos);
int				add_sep(t_lexer **lexer, char *line, int pos, int *cmd);
int				add_word(t_lexer **lexer, char *line, int pos, int cmd);

/* IS_TOKEN */

int				is_escape(char *line, int pos);
int				is_sep(char *line, int pos);
int				is_space(int c);
int				is_double_chevron(char *line, int pos);

/* HANDLE_QUOTES */

int				handle_quotes(char *line, int pos, int quote, char c);
int				select_quote(char *line, int pos, int quote);
int				quoted_word(t_lexer **lexer, char *line, int pos, int cmd);
int				is_in_dquotes(char *line, int pos);
int				is_in_squotes(char *line, int pos);

/* LEXER_UTILS */

char			*ft_charjoin(char *s1, char c);
t_lexer			*ft_lstnew_minishell(void *content);
t_lexer			*ft_lstlast_minishell(t_lexer *lst);
void			ft_lstadd_back_minishell(t_lexer **lst, t_lexer *new);

/* ********************************************************** */
/*                           PARSING                          */
/* ********************************************************** */

/* PARSER */

int				ft_parser(t_data **data);

/* PARSER_UTILS */

int				ft_error(int error, char *str);
int				ft_lexerlen(t_lexer *lexer);
void			ft_strcpy(char *dest, char *src);

/* TOKEN_TYPE_ERROR */

t_token_type	token_type_chevron(t_data **data, int i);
t_token_type	token_type(t_data **data, int i);
t_token_type	is_chevron_type(t_data **data, int i);
int				select_chevron_error(t_data **data, int i);
int				error_type_token(t_data **data);

/* INIT_PARSING */

void			select_file(t_data **data, int i);
void			assign_file(t_data **data);
void			init_finish_token(t_data **data, int i);
void			init_parsing(t_data **data);

/* CONVERT_ENV */

int				find_dollar_index(char *str, int end);
int				active_var(char *str, int j);
int				dollar_in_squote(t_data **data, char *str, int i, int ip);
char			*parse_dollar(t_data **data, char **env, char *str, int ip);
void			convert_env(t_data **data);

/* CONVERT_ENV_UTILS */

void			bool_quote(int *quote1, int *quote2);
int				check_env(char **env, char *str);
void			ft_varcpy(char *var, char *str, int *i, int j);
int				check_dollar(char *str);
char			*ft_varjoin(char *new_str, char *str, char **env, int *i);

/* CONVERT_ENV_UTILS2 */

int				is_parse_sep(char *str, int i);
char			*ft_strjoin_env(char *new_str, char *env_ptr);
char			*ft_codejoin(t_data **data, char *new_str, int *i);
t_parse			ft_structcpy(t_parse dest, t_parse src);
t_parse			*ft_parsejoin(t_parse *new_parse, t_parse parse);

/* PARSE_QUOTES */

int				parse_quotes(t_data **data);
char			*ft_parsing(char *str);
char			*parse_quote(int c, char *new_str, int *quote1, int *quote2);
int				only_quote(char *str);
int				is_quotes(char *str);

/* REFRESH_PARSE */

int				ft_parse_count(char *str);
char			*ft_parse_word(char *str, int i);
char			**ft_parse_split(char *str);
t_parse			*ft_check_space(t_parse *new_parse, t_parse parse);
t_parse			*ft_refresh_parse(t_data **data);

/* ********************************************************** */
/*                           EXECUTION                        */
/* ********************************************************** */

/* MAIN */

void			process(t_data **data);
void			child_process(t_data *data, int cmd);
void			exec_process(t_data *data);
void			execution(t_data *data);
void			exec_builtout(t_data *data);
void			execute(t_data *data, int cmdnb, int builtin, char **bash);

/* FD MANAGER */

int				handle_fd(t_data *data, int cmd);
int				fd_infile(t_data *data, int cmd);
int				fd_outfile(t_data *data, int cmd);
int				fd_heredoc(t_data *data, int cmd, int status);

/* PROCESS UTILS */

/* UTILS */
t_files			*getfiles(int file, int cmd, t_data *data);
t_exec			exec_finish(t_exec exec, t_data *data, int cmd);
int				is_builtin(t_data *data);
int				is_same_string(char *line, char *limiter);
void			heredoc_boucle(t_data *data, int i, int cmd, int status);
int				handle_infile(t_data *data, int cmd, int i);
t_token_type	get_outfile_type(t_data *data, int cmd, int j);
int				handle_outfile(t_data *data, int cmd, int i);
char			**find_path(char **e);
char			*find_cmdpath(char *cmd, char **envp);
char			**test(char **lol);
char			**getcmd(t_data *data, int cmdnb);
int				gotoparsecmd(t_data *data, int cmd);
char			*setpath(char *cmd, char **envp);
int				is_path(char *av);
void			print_both(t_data *data);
int				getwords(t_data *data, int cmdnb);
void			err_return(char **cmd);
void			close_pipes(t_data *data);
void			print_double(char **db);
void			free_double(char **lol);
int				getargsnb(t_parse *parse);
int				islastinfile(t_data *data, t_files *file, int i, int cmd);
int				islastfile(t_files *file, int i);
int				ft_ambigous(t_data *data, int cmd, char c, int index);
int				trybuiltin(t_data *data, char **cmd);
int				getcode(t_data *data);
int				ft_ultracmp(char *first, char *second);
t_files			exec_file_process(char *parse);

/* ********************************************************** */
/*                           SIGNAL                           */
/* ********************************************************** */

void			sig_handler(int _);
void			sig_init(void);

#endif