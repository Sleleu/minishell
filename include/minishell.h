/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/20 18:23:48 by rvrignon         ###   ########.fr       */
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

int 			ft_unset(char **env, char *line);

/* MEMCENTER */

void			*memcenter(t_mem mem, size_t size, void *adress, t_label label);

void			*mempurge(t_memcenter *head);

void			*memfree(t_memcenter *head, void *adress);

void			*memfreewhere(t_memcenter *head, t_label label);

void			*first_malloc(size_t size, void *adress, t_label label);

void			*after_malloc(size_t size, void *adress, t_label label);

/* LEXER */

t_lexer			*ft_lexer(char *line);

char			*ft_charjoin(char *s1, char c);

t_lexer			*ft_lstnew_minishell(void *content);

t_lexer			*ft_lstlast_minishell(t_lexer *lst);

void			ft_lstadd_back_minishell(t_lexer **lst, t_lexer *new);

int				is_sep(char *line, int pos);

int				is_space(char *line, int pos);

int 			is_double_chevron(char *line, int pos);

int				select_chevron(t_lexer **token, char *line, int pos);

int				add_sep(t_lexer **lexer, char *line, int pos);

int				add_word(t_lexer **lexer, char *line, int pos);

int 			handle_quotes(char *line, int pos, int quote, char c);

int				quoted_word(t_lexer **lexer, char *line, int pos);

/* PARSING */

int				ft_parser(t_data **data);

/* EXECUTION */

int				process(t_data **data);

#endif