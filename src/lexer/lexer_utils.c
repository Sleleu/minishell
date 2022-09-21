/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:44:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/21 12:48:26 by sleleu           ###   ########.fr       */
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
	str = memcenter(MALLOC, sizeof(char) * size + 2, NULL, LEXER);
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

	new = memcenter(MALLOC, sizeof(t_lexer), NULL, LEXER);
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
