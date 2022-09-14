/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/14 16:01:00 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <limits.h>

/* GLOBAL */

typedef struct s_data
{
	char *line;
	char **env;
	char *prompt;
	int nb;
	
}	t_data;

/* UTILS */

int	ft_pwd(void);

void ft_env(char **env);

int	ft_echo(char *line);

void ft_unset(char **env, char *line);

t_data *get_data(void);

t_data *set_data(char **env);

t_data *update_data(char *line);

void ft_parser(char *line);

#endif