/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:09:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/16 00:28:09 by sleleu           ###   ########.fr       */
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
	str = memcenter(MALLOC, sizeof(char) * size + 2, NULL, "charjoin");
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

	new = memcenter(MALLOC, sizeof(t_lexer), NULL, "listnew");
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

void	add_sep(t_lexer **lexer, char *line, int pos)
{
	t_lexer	*token;
	
	token = *lexer;
	token = ft_lstnew_minishell(NULL);
	if (line[pos] == '|')
		token->type = PIPE;
	else if (line[pos] == '<')
		token->type = INF_CHEVRON; // SUITE ICI
	ft_lstadd_back_minishell(lexer, token);
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
		{
			add_sep(&lexer, line, pos);
			pos++;
		}
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