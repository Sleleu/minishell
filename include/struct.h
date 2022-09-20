/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:15:45 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/20 14:04:04 by rvrignon         ###   ########.fr       */
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

/* PIPE */

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
	PURGE = 1,
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
	struct s_lexer *lexer;
	t_pipe	*pipes;
	t_memcenter	*memcenter;
}	t_data;

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
	char *content;
	t_token_type	type;
	struct s_lexer *next;
}	t_lexer;

#endif