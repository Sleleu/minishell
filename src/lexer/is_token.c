/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:42:31 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/02 19:54:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_sep(char *line, int pos)
{
	if (line[pos] == '|' || line[pos] == '>' || line[pos] == '<')
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
