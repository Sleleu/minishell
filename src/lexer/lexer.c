/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:09:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/15 00:51:44 by sleleu           ###   ########.fr       */
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
	REDIR = 3,
	D_REDIR = 4
	S_QUOTE = 5;
	D_QUOTE = 6;	
}	token_type;

typedef struct s_token
{
	char *content;
	int	type;
	int	size;
}	t_token;

int	space_in_quote(char *line, int i)
{
	int	j; // back
	int k; // forward
	int quote_j;
	int quote_k;
	
	quote_j = 0;
	quote_k = 0;
	j = i;
	k = i;
	while (line[j] && (line[j] != '"' ||)) // useless
}

int	check_sep(char *line, int i)
{
	if ((*line + i) == ' ' || (*line + i) == '"'
		|| (*line + i == 39)) // simple quote
		return (1);
	else
		return (0);
}

char **alloc_array(char **token, char *line)
{
	int	i;
	int	nb_tokens;

	i = 0;
	nb_tokens = 0;
	while (line[i])
	{
		while (line[i] && line[])
			i++;
		if (line[i] && check_sep(line, i) && !space_in_quote(line, i))
			nb_tokens++;
		while (line[i] && !chek_sep)
			i++;
	}
	tokens = ft_calloc(sizeof(char *), nb_tokens + 1);
	if (!tokens)
		return (NULL)
	return (tokens);
}
/*
void	lexer(t_data *data, char *line)
{
	int	i;
	char **tokens; // tableau tokens
	
	i = 0;
	if ((tokens = alloc_array(tokens, line)) == NULL)
		return ; // ERROR ICI
	while (*line)
	{
		if (is
	}
}*/

void	lexer(t_data *data, char *line)
{
	int pos;
	int i;
	t_token *lexer;

	pos = 0;
	i = 0;
	if ((tokens = alloc_array(tokens, line)) == NULL)
		return ; // ERROR
	while (line[pos])
	{
		if (line[pos] == ' ')
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
