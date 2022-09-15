/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/15 23:08:47 by rvrignon         ###   ########.fr       */
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

typedef struct s_pipe
{
	char			*line;
	char			*cmd;
	char			*option;
	int				*fd;
	int				oldfd;
	struct s_pipe	*next;
	struct s_pipe	*prev;
}	t_pipe;

/* MEMCENTER STRUCT */

typedef enum e_mem 
{
	FLUSH = 1,
	FREE = 2,
	MALLOC = 3,
}	t_mem;

typedef struct s_memcenter
{
	void				*adress;
	char				*hello;
	struct s_memcenter	*next;
}	t_memcenter;

 typedef struct s_data
 {
	char	*line;
	char	**env;
	char	*prompt;
	int		nb;
	t_pipe	*pipes;
	t_memcenter	*memcenter;
}	t_data;

/* UTILS */

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

void			*memflush(t_memcenter *head);

void			*memfree(t_memcenter *head, void *adress);

int				freetab(char **test);

void			*first_malloc(size_t size, void *adress, char *label);

void			*after_malloc(size_t size, void *adress, char *label);

void			*memcenter(t_mem mem, size_t size, void *adress, char *label);

#endif