/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:15:45 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/20 19:28:34 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <limits.h>

/* PIPEX */

typedef struct s_pipex{
	int		ac;
	char	**av;
	char	**envp;
	int		i;
	pid_t	pid;
	int		fd[2];
	int		oldfd;
	int		heredoc;
}	t_pipex;

/* MEMCENTER STRUCT */

typedef enum e_mem
{
	PURGE = 1,
	FREE = 2,
	FREE_WHERE = 3,
	MALLOC = 4,
}	t_mem;

typedef	enum e_label
{
	NOTHING = 0,
	BUILTIN = 1,
	LEXER = 2,
	PARSING = 3,
}	t_label;

typedef struct s_memcenter
{
	void				*adress;
	t_label				label;
	struct s_memcenter	*next;
}	t_memcenter;

/* LEXER */

typedef enum e_token_type
{
	WORD = 1,
	PIPE = 2,
	INF_CHEVRON = 3,
	SUP_CHEVRON = 4,
	D_INF_CHEVRON = 5,
	D_SUP_CHEVRON = 6,
	DOLLAR = 7,
}	t_token_type;

typedef struct s_lexer
{
	char 			*content;
	t_token_type	type;
	struct s_lexer 	*next;
}	t_lexer;

/* PARSING */

typedef struct s_parse
{
	char				*str;
	t_token_type		type;
}	t_parse;

// GLOBAL STRUCT

 typedef struct s_data
 {
	char		*line;
	char		**env;
	t_lexer		*lexer;
	t_pipex		*pipex;
	t_parse		*parse;
	t_memcenter	*memcenter;
}	t_data;

#endif