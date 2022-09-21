/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:52:52 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/21 13:07:32 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	quoted_word(t_lexer **lexer, char *line, int pos)
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
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}
