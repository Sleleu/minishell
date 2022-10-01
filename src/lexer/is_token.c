/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:42:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/01 02:21:44 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	is_escape(char *line, int pos)
{
	int	nb_sep;

	nb_sep = 0;
	if (line[pos] == '\\')
	{
		if (line[pos - 2] && line[pos - 2] == '\\')
		{
			while (pos > 0 && line[pos] == '\\')
			{
				pos--;
				nb_sep++;
				if (nb_sep % 2 == 0)
					return (0);
				return (1);
			}
		}
		else if (line[pos - 1] && line[pos - 1] == '\\')
			return (0);
		else
			return (1);
	}
	return (0);
}*/

int	is_sep(char *line, int pos)
{
	if (line[pos] == '|' || line[pos] == '>'
		|| line[pos] == '<'/* || (line[pos] == '$'
			&& (ft_isalpha(line[pos + 1]) || line[pos + 1] == '_')*/)
			return (1);
		return (0);
}

int	is_space(int c)
{
	if ((c >= 9 && c <= 13)
		|| c == ' ')
		return (1);
	else
		return (0);
}

int	is_double_chevron(char *line, int pos)
{
	if (line[pos] == '>' && line[pos + 1] == '>')
		return (1);
	else if (line[pos] == '<' && line[pos + 1] == '<')
		return (2);
	else
		return (0);
}
