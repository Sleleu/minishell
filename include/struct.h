/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:15:45 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/26 14:55:30 by rvrignon         ###   ########.fr       */
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
# include <sys/wait.h>

/* PIPEX */

typedef struct s_exec{
	char	*infile;
	char	*outfile;
	int		cmd;
	pid_t	pid;
}	t_exec;

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
	EXEC = 3,
	PARSING = 4,
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
	INFILE = 8,
	OUTFILE_T = 9,
	OUTFILE_A = 10,
	LIMITER = 11,
	FINISH = 12,
}	t_token_type;

typedef struct s_lexer
{
	char 			*content;
	int				cmd;
	t_token_type	type;
	struct s_lexer 	*next;
}	t_lexer;

/* PARSING */

typedef struct s_parse
{
	char				*str;
	int					cmd;
	t_token_type		type;
}	t_parse;

// GLOBAL STRUCT

 typedef struct s_data
 {
	int			actual;
	int			args;
	char		*line;
	char		**env;
	t_lexer		*lexer;
	t_exec		*exec;
	t_parse		*parse;
	t_memcenter	*memcenter;
	pid_t		pid;
	int			fd[2];
	int			oldfd;
}	t_data;
#endif