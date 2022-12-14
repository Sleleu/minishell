/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:52:52 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/01 15:28:06 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_dquotes(char *line, int pos)
{
	int	i;
	int	d_quote;

	d_quote = 0;
	i = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == '"')
			d_quote++;
		i++;
	}
	if (d_quote % 2 == 1)
		return (1);
	else
		return (0);
}

int	is_in_squotes(char *line, int pos)
{
	int	i;
	int	s_quote;

	s_quote = 0;
	i = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == 39)
			s_quote++;
		i++;
	}
	if (s_quote % 2 == 1)
		return (1);
	else
		return (0);
}

int	handle_quotes(char *line, int pos, int quote, char c)
{
	if (line[pos + 1])
	{
		if (line[pos + 1] == '|' || line[pos + 1] == ' ')
		{
			if (line[pos] == c && quote % 2 == 1)
				return (0);
			else if (line[pos] == c && quote % 2 == 0)
				return (1);
			else if (line[pos] != c && quote % 2 == 0)
				return (0);
			else if (line[pos] != c && quote % 2 == 1)
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	select_quote(char *line, int pos, int quote)
{
	if (line[pos] == '"')
	{
		while (handle_quotes(line, pos, quote, '"'))
		{
			if (line[pos] == '"')
				quote++;
			pos++;
		}
	}
	else if (line[pos] == 39)
	{
		while (handle_quotes(line, pos, quote, 39))
		{
			if (line[pos] == 39)
				quote++;
			pos++;
		}
	}
	return (pos);
}

int	quoted_word(t_lexer **lexer, char *line, int pos, int cmd)
{
	int		index;
	int		quote;
	t_lexer	*token;

	token = *lexer;
	index = pos - 1;
	token = ft_lstnew_minishell(NULL);
	quote = 0;
	pos = select_quote(line, pos, quote);
	pos++;
	while (++index < pos)
		token->content = ft_charjoin(token->content, line[index]);
	token->type = WORD;
	token->cmd = cmd;
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}
