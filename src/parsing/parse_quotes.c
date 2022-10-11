/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:11:00 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/11 02:21:49 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*parse_quote(int c, char *new_str, int *quote1, int *quote2)
{
	if (*quote1 == 1)
		new_str = ft_charjoin(new_str, c);
	else if (*quote2 == 0)
		*quote2 = 1;
	else if (*quote2 == 1)
		*quote2 = 0;
	return (new_str);
}

char	*ft_parsing(char *str)
{
	int		i;
	char	*new_str;
	int		d_quote;
	int		s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	new_str = "";
	while (str[i])
	{
		if (str[i] == '"')
			new_str = parse_quote(str[i], new_str, &s_quote, &d_quote);
		else if (str[i] == 39)
			new_str = parse_quote(str[i], new_str, &d_quote, &s_quote);
		else
			new_str = ft_charjoin(new_str, str[i]);
		i++;
	}
	if (((d_quote == 1 || s_quote == 1)))
		return (NULL);
	return (new_str);
}

int	only_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 39 && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

int	parse_quotes(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].str != NULL && is_quotes((*data)->parse[i].str))
		{
			(*data)->parse[i].str = ft_parsing((*data)->parse[i].str);
			if (!(*data)->parse[i].str)
			{
				printf("unclosed_quotes\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
