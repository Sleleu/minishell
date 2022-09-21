/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/21 14:27:49 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

/* INIT */

t_data 			*get_data(void);

t_data 			*set_data(char **env);

/* BUILTIN */

int				ft_pwd(void);

int 			ft_env(char **env);

int				ft_echo(char *line);

int				ft_cd(char *line);

int 			ft_unset(char **env, char *line);

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

int				add_sep(t_lexer **lexer, char *line, int pos);

int				add_word(t_lexer **lexer, char *line, int pos);

/* IS_TOKEN */

int				is_sep(char *line, int pos);

int				is_space(char *line, int pos);

int 			is_double_chevron(char *line, int pos);

/* HANDLE_QUOTES */

int 			handle_quotes(char *line, int pos, int quote, char c);

int				select_quote(char *line, int pos, int quote);

int				quoted_word(t_lexer **lexer, char *line, int pos);

/* LEXER_UTILS */

char			*ft_charjoin(char *s1, char c);

t_lexer			*ft_lstnew_minishell(void *content);

t_lexer			*ft_lstlast_minishell(t_lexer *lst);

void			ft_lstadd_back_minishell(t_lexer **lst, t_lexer *new);

/* ********************************************************** */
/*                           PARSING                          */
/* ********************************************************** */

/* PARSER */

int			ft_parser(t_data **data);

/* PARSER_UTILS */

int				ft_error(int error, char *str);

int				ft_lexerlen(t_lexer *lexer);

void			ft_strcpy(char *dest, char *src);

/* ********************************************************** */
/*                           EXECUTION                        */
/* ********************************************************** */

int				process(t_data **data);

t_parse			*simulate_parse(t_parse *parsing);

#endif