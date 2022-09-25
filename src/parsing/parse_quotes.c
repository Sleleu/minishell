/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:11:00 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/25 21:28:04 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_even_quotes_str(char *str, int *d_quotes)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			*d_quotes += 1;
		i++;
	}
}


int	check_even_quotes(t_parse *parse)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (parse[i].type != FINISH)
	{
		if (parse[i].str != NULL)
			check_even_quotes_str(parse[i].str, &d_quotes);
		i++;
	}
	if (s_quotes % 2 == 1 || d_quotes % 2 == 1)
		return (0);
	return (1);
}


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

// retourne 1 si la lettre se trouve dans des quotes

int	char_in_d_quotes(char *str, int i)
{
	int	j;
	int	d_quotes;

	j = 0;
	d_quotes = 0;
	while (str[j] && j < i + 1)
	{
		if (str[j] == '"')
			d_quotes++;
		j++;
	}
	if (d_quotes % 2 == 1)
		return (1);
	return (0);
}

char 	*check_quotes(char *str)
{
	char *new_str;
	int	i;

	i = 1;
	new_str = NULL;
	while (str[i])
	{
		if (char_in_d_quotes(str, i))
			new_str = ft_charjoin(new_str, str[i]);
		i++;
	}
	return (new_str);
}


int	parse_quotes(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].str != NULL && is_quotes((*data)->parse[i].str))
			(*data)->parse[i].str = check_quotes((*data)->parse[i].str);
		i++;
	}
	
	if (!check_even_quotes((*data)->parse))
	{
		printf("minishell: unclosed quotes\n");
		return (0);
	}
	return (1);
}