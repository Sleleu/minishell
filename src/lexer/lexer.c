/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:09:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/30 00:29:11 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	select_chevron(t_lexer **token, char *line, int pos)
{
	if (line[pos + 1] && is_double_chevron(line, pos))
	{
		if (is_double_chevron(line, pos) == 1)
			(*token)->type = D_SUP_CHEVRON;
		else if (is_double_chevron(line, pos) == 2)
			(*token)->type = D_INF_CHEVRON;
		pos += 2;
	}
	else
	{
		if (line[pos] == '<')
			(*token)->type = INF_CHEVRON;
		else if (line[pos] == '>')
			(*token)->type = SUP_CHEVRON;
		pos++;
	}
	return (pos);
}

int	add_sep(t_lexer **lexer, char *line, int pos, int *cmd)
{
	t_lexer	*token;

	token = *lexer;
	token = ft_lstnew_minishell(NULL);
	if (line[pos] == '|')
	{
		token->type = PIPE;
		pos++;
		*cmd += 1;
	}
	else if (line[pos] == '<' || line[pos] == '>')
		pos = select_chevron(&token, line, pos);
	else if (line[pos] == '$')
	{
		token->type = DOLLAR;
		pos++;
	}
	token->cmd = *cmd;
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}

int	is_in_quotes(char *line, int pos)
{
	int	i;
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == 39)
			s_quote++;
		else if (line[i] == '"')
			d_quote++;
		i++;
	}
	if (d_quote % 2 == 1 || s_quote % 2 == 1)
		return (1);
	else
		return (0);
}

int	add_word(t_lexer **lexer, char *line, int pos, int cmd)
{
	t_lexer	*token;

	token = *lexer;
	token = ft_lstnew_minishell(NULL);
	if (!token)
		return (-1);
	token->type = WORD;
	while (line[pos] && !is_sep(line, pos))
	{
		if (is_space(line[pos]) && !is_in_quotes(line, pos))
			break;
		token->content = ft_charjoin(token->content, line[pos]);
		pos++;
	}
	token->cmd = cmd;
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}

t_lexer	*ft_lexer(char *line)
{
	int		pos;
	int		cmd;
	t_lexer	*lexer;

	pos = 0;
	cmd = 1;
	lexer = NULL;
	while (line[pos])
	{
		if (is_space(line[pos]))
			pos++;
		else if (is_sep(line, pos))
			pos = add_sep(&lexer, line, pos, &cmd);
		else if (line[pos] == '"' || line[pos] == 39)
			pos = quoted_word(&lexer, line, pos, cmd);
		else
		{
			pos = add_word(&lexer, line, pos, cmd);
			if (pos == -1)
				return (NULL);
		}
	}
	return (lexer);
}

// ERROR A GERER SUR LE RETURN NUL
/*
int	main(int ac, char **av)
{
	t_lexer *lexer;

	if (ac == 2)
	{
		lexer = ft_lexer(av[1]);
		while (lexer)
		{
			printf("content : %s | type : %d\n", lexer->content, lexer->type);
			lexer = lexer->next;
		}
	}
	memcenter(FLUSH, 0, NULL, NULL);
	return (0);
}
*/