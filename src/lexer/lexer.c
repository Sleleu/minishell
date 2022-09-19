/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:09:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/19 23:27:04 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_charjoin(char *s1, char c)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	size = 0;
	while (s1 && s1[size])
		size++;
	str = memcenter(MALLOC, sizeof(char) * size + 2, NULL, NULL);
	if (str == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	return (str);
}

t_lexer	*ft_lstnew_minishell(void *content)
{
	t_lexer	*new;

	new = memcenter(MALLOC, sizeof(t_lexer), NULL, NULL);
	if (!new)
		return (NULL);
	if (!content)
		new->content = NULL;
	else
		new->content = content;
	new->next = NULL;
	return (new);
}

t_lexer	*ft_lstlast_minishell(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	else
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
}

void	ft_lstadd_back_minishell(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (*lst)
	{
		last = ft_lstlast_minishell(*lst);
		last->next = new;
	}
	else
		*lst = new;
}


int	is_sep(char *line, int pos)
{
	if (line[pos] == '|' || line[pos] == '>'
		|| line[pos] == '<' || line[pos] == '$')
		return (1);
	else
		return (0);
}

int	is_space(char *line, int pos)
{
	if ((line[pos] >= 9 && line[pos] <= 13)
		|| line[pos] == ' ')
		return (1);
	else
		return (0);
}

int is_double_chevron(char *line, int pos)
{
	if (line[pos] == '>' && line[pos + 1] == '>')
		return (1);
	else if (line[pos] == '<' && line[pos + 1] == '<')
		return (2);
	else
		return (0);
}

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
	return(pos);
}

int	add_sep(t_lexer **lexer, char *line, int pos)
{
	t_lexer	*token;
	
	token = *lexer;
	token = ft_lstnew_minishell(NULL);
	if (line[pos] == '|')
	{
		token->type = PIPE;
		pos++;
	}
	else if (line[pos] == '<' || line[pos] == '>')
		pos = select_chevron(&token, line, pos);
	else if (line[pos] == '$')
	{
		token->type = DOLLAR;
		pos++;
	}
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}

int	add_word(t_lexer **lexer, char *line, int pos)
{
	t_lexer *token;

	token = *lexer;
	token = ft_lstnew_minishell(NULL);
	if (!token)
		return (-1);
	token->type = WORD;
	while (line[pos] && !is_space(line, pos) && !is_sep(line, pos))
	{
		token->content = ft_charjoin(token->content, line[pos]);
		pos++;
	}
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}

int	quoted_word(t_lexer **lexer, char *line, int pos)
{
	int index;
	int	quote;
	t_lexer *token;

	token = *lexer;
	index = pos;
	token = ft_lstnew_minishell(NULL);
	quote = 0;
	if (line[pos] == '"')
	{
		while (line[pos + 1] && !(line[pos] == '"' && line[pos + 1] != '"' && quote % 2 == 1))
		{
			if (line[pos] == '"')
				quote++;
			pos++;
		}
	}
	else if (line[pos] == 39)
	{
		while (line[pos + 1] && !(line[pos] == 39 && line[pos + 1] != 39 && quote % 2 == 1))
			{
				if (line[pos] == 39)
					quote++;
				pos++;
			}
	}
	pos++;
	while (index < pos)
	{
		token->content = ft_charjoin(token->content, line[index]);
		index++;
	}
	token->type = WORD;
	ft_lstadd_back_minishell(lexer, token);
	return (pos);
}

t_lexer	 *ft_lexer(char *line)
{
	int		pos;
	t_lexer	*lexer;
	
	pos = 0;
	lexer = NULL;
	while (line[pos])
	{
		if (is_space(line, pos))
			pos++;
		else if (is_sep(line, pos))
			pos = add_sep(&lexer, line, pos);
		else if (line[pos] == '"' || line[pos] == 39)
			pos = quoted_word(&lexer, line, pos);
		else
		{
			pos = add_word(&lexer, line, pos);
			if (pos == -1)
				return (NULL); // ERROR A GERER
		}
	}
	return (lexer);
}

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