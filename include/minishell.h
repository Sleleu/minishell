/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/19 14:46:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

int				ft_pwd(void);

void 			ft_env(char **env);

int				ft_echo(char *line);

void 			ft_unset(char **env, char *line);

t_data 			*get_data(void);

t_data 			*set_data(char **env);

t_data 			*update_data(char *line);

void 			ft_parser(char *line);

int				pipe_exist(char *line);

t_pipe 			*pipe_addlast(t_pipe *pipe, char *line);

t_pipe 			*create_pipes(char *line);

void			*memcenter(t_mem mem, size_t size, void *adress, char *label);

void			*memflush(t_memcenter *head);

void			*memfree(t_memcenter *head, void *adress);

void			*first_malloc(size_t size, void *adress, char *label);

void			*after_malloc(size_t size, void *adress, char *label);

/* LEXER */

t_lexer	*ft_lexer(char *line);

#endif