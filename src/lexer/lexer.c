/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:09:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/15 21:17:58 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
	WORD = 1,
	PIPE = 2,
	SIMPLE_QUOTE = 3,
	DOUBLE_QUOTE = 4,
	INF_CHEVRON = 5,
	SUP_CHEVRON = 6,
	D_INF_CHEVRON = 7,
	D_SUP_CHEVRON = 8,
}	token_type;

typedef struct s_token
{
	char *content;
	int	type;
	int	size;
	struct s_token next;
}	t_token;

int	is_sep(char *line, int pos)
{
	if (line[pos] == '|' || line[pos] == '>'
		|| line[pos] == '<' || line[pos] == '>>'
		|| line[pos] == '<<' || line[pos] == '$')
		return (1);
	return (0);
}

t_token	 *lexer(t_data *data, char *line)
{
	int		pos;
	int		i;
	t_token	*lexer;
	
	pos = 0;
	i = 0;
	lexer = NULL;
	// INITIALISER LISTE
	while (line[pos])
	{
		if (line[pos] >= 9 && line[pos] <= 13 || line[pos] == ' ') // espace ignore
			pos++;
		else if (is_sep(line, pos)) // si pas un mot
		{
			add_sep(&lexer, line, pos);
			pos++;
		}
		else
		{
			add_word(&lexer, line, pos);
			pos++;
		}
	}
	return (lexer);
}

int	main(void)
{
	
	return (0);
}
		/*
			pos++;
		if (is_char(line, pos))
		{
			token[i].type = WORD;
			while (is_char(line, pos))
			{
				token[i].size++ // set a 0 les datas de la struct
				pos++;
				//ft_strjoin(token[i].content, line[pos]) // set a NULL les char* de la struct + transformer strjoin en charjoin
			}
			i++;
		}
		else if (is_pipe(line, pos))
		{
			token[i].type = PIPE;
			//ft_strjoin(token[i].content, line[pos]) // set a NULL les char* de la struct + transformer strjoin en charjoin
			pos++;
			i++;
		}
		else if (is_redirect(line, pos))
		{
			if (is_redirect(line, pos + 1))
			{
				token[i].size += 2;
				token[i].type = D_REDIR;
				//charjoin les deux
				pos += 2;
				i++;	
			}
			else
			{
				token[i].size = 1; // si token existe donc forcement 1 alors set size a 1 ?
				token[i].type = REDIR;
				//charjoin
				pos++;
				i++;
			}
		}
	}
}

/* 

Tableau de structures
t_token *lexer;
checker algo de la descente recursive

*/
