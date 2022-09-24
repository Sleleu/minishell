/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/25 01:26:32 by sleleu           ###   ########.fr       */
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

int				is_sep(char *line, int pos);
int				is_space(char *line, int pos);
int 			is_double_chevron(char *line, int pos);

/* HANDLE_QUOTES */

int 			handle_quotes(char *line, int pos, int quote, char c);
int				select_quote(char *line, int pos, int quote);
int				quoted_word(t_lexer **lexer, char *line, int pos, int cmd);

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

int				check_env(char **env, char *str);
void			convert_env(t_data **data);

/* ********************************************************** */
/*                           EXECUTION                        */
/* ********************************************************** */

int				process(t_data **data);
int				exec_simple(t_data *data);
int				exec_pipes(t_data *data);
int				exec(t_data *data);
void			exec_simple_process(t_data *data);
void			exec_pipes_process(t_data *data);
void			close_pipes(t_data *data);
void			error(void);
void			print(char *s);
char			**find_path(char **e);
char			*find_cmdpath(char *cmd, char **envp);
char			*setpath(char *av, char **envp);
int				is_path(char *av);
char 			**test(char **lol);
void			execute(t_data *data, int cmd);
void			free_double(char **lol);
void			err_return(char **cmd);
void			print_both(t_data *data);
int				exec(t_data *data);
int				builtin(t_data **data);
int				getcmdnb(t_parse *parse);

#endif