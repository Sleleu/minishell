/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/01 15:12:14 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/* ********************************************************** */
/*                           INIT                             */
/* ********************************************************** */

t_data 			*get_data(void);
t_data 			*set_data(char **env);
void			restore_data(void);

/* ********************************************************** */
/*                          BUILTIN                           */
/* ********************************************************** */

int				ft_pwd(void);
int 			ft_env(char **env);
int				ft_echo(t_parse *parse);
int				ft_cd(char *line);
int 			ft_unset(char **env, char *line);

/* EXPORT */

int				export_error_num(t_parse *parse, int i);
int				ft_export_check_arg(t_data **data, t_parse *parse);
void			ft_refresh_var(t_data **data, char *str, int index_equal);
void			ft_export_action(t_data **data, char *str, int index_equal);
int				ft_export(t_data **data, t_parse *parse);

/* EXPORT_IS_VAR */

int				is_env_variable(char *str, int *code);
int				isalnum_var(char *str, int index_equal);
int				is_new_var(char **env, char *str, int index_equal);

/* EXPORT UTILS */

char			**ft_envjoin(char **env, char *str);
char 			*ft_strdel(char *str, char c, int n);
char			**ft_append_var(char **env, char *str, int index_equal);

/* EXIT */

long long int	ft_long_atoi(char *str);
int				exit_numeric_error(char *str);
int				exit_error(t_parse *parse);
int				ft_exit(t_parse *parse);

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
int 			is_double_chevron(char *line, int pos);

/* HANDLE_QUOTES */

int 			handle_quotes(char *line, int pos, int quote, char c);
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

char			*parse_dollar(t_data **data, char **env, char *str, int index_parse);
void			convert_env(t_data **data);

/* PARSE_QUOTES */

int				parse_quotes(t_data **data);
char			*ft_parsing(char *str);
char			*parse_squote(int c, char *new_str, int *d_quote, int *s_quote);
char			*parse_dquote(int c, char *new_str, int *d_quote, int *s_quote);
int				is_quotes(char *str);

/* ********************************************************** */
/*                           EXECUTION                        */
/* ********************************************************** */

/* PROCESS */

int				process(t_data **data);
void			execute(t_data *data, int cmdnb);
void			exec_process(t_data *data);
void			child_process(t_data *data, int cmd);
int				handle_fd(t_data *data, int cmd);
int				handle_infile(t_data *data, int cmd);
int				handle_outfile(t_data *data, int cmd);
void			handle_heredoc(t_data *data, int cmd, int status);
t_token_type 	get_outfile_type(t_data *data, int cmd);
int				execution(t_data *data);

/* PROCESS UTILS */

char			**find_path(char **e);
char			*find_cmdpath(char *cmd, char **envp);
char			*setpath(char *cmd, char **envp);
int				is_path(char *av);
char 			**test(char **lol);
char			**getcmd(t_data *data, int cmdnb);
int				islastinfile(t_data *data, char *infile, int cmd);

/* UTILS */

void			print_both(t_data *data);
void			free_double(char **lol);
void 			print_double(char **db);
void			close_pipes(t_data *data);
void			err_return(char **cmd);
int				builtin(t_data **data);
int				getargsnb(t_parse *parse);

/* ********************************************************** */
/*                           SIGNAL                           */
/* ********************************************************** */

void	sig_init(void);

#endif