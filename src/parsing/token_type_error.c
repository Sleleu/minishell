/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:03 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/22 13:39:47 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	token_type(t_data **data, int i)
{
	if ((*data)->parse[i].type == WORD)
		return (WORD);
	else if ((*data)->parse[i].type == PIPE)
		return (PIPE);
	else if ((*data)->parse[i].type == INF_CHEVRON)
		return (INF_CHEVRON);
	else if ((*data)->parse[i].type == SUP_CHEVRON)
		return (SUP_CHEVRON);
	else if ((*data)->parse[i].type == D_INF_CHEVRON)
		return (D_INF_CHEVRON);
	else if ((*data)->parse[i].type == D_SUP_CHEVRON)
		return (D_SUP_CHEVRON);
	else if ((*data)->parse[i].type == DOLLAR)
		return (DOLLAR);
	else if ((*data)->parse[i].type == INFILE)
		return (INFILE);
	else if ((*data)->parse[i].type == OUTFILE_T)
		return (OUTFILE_T);
	else if ((*data)->parse[i].type == OUTFILE_A)
		return (OUTFILE_A);
	else if ((*data)->parse[i].type == LIMITER)
		return (LIMITER);
	else if ((*data)->parse[i].type == FINISH)
		return (FINISH);
	else
		return (0);
}

t_token_type	is_chevron_type(t_data **data, int i)
{
	if (token_type(data, i) >= INF_CHEVRON && token_type(data, i) <= D_SUP_CHEVRON)
		return (token_type(data, i));
	else
		return (0);
}

int	select_chevron_error(t_data **data, int i)
{
	if (token_type(data, i - 1) == INF_CHEVRON && token_type(data, i) == SUP_CHEVRON)
		printf("minishell: syntax error near unexpected token `newline'\n");
	if (token_type(data, i) == INF_CHEVRON)
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (token_type(data, i) == SUP_CHEVRON)
		printf("minishell: syntax error near unexpected token `>'\n");
	else if (token_type(data, i) == D_INF_CHEVRON)
		printf("minishell: syntax error near unexpected token `<<'\n");
	else if (token_type(data, i) == D_SUP_CHEVRON)
		printf("minishell: syntax error near unexpected token `>>'\n");
	return (2);
}

int	error_type_token(t_data **data)
{
	int	i;

	i = 0;
	if ((*data)->parse[0].type == PIPE)
		return (ft_error(2,
				"minishell: syntax error near unexpected token `|'"));
	while (token_type(data, i) != FINISH)
	{
		if (token_type(data, i + 1) != FINISH && token_type(data, i) == PIPE
			&& token_type(data, i + 1) == PIPE)
			return (ft_error(2,
					"minishell: syntax error near unexpected token `|'"));
		else if (token_type(data, i + 1) != FINISH && (is_chevron_type(data, i)
				&& is_chevron_type(data, i + 1)))
			return (select_chevron_error(data, i + 1));
		else if (token_type(data, i + 1)
				&& (is_chevron_type(data, i) && token_type(data, i + 1) == PIPE))
			return (ft_error(2, "minishell: syntax error near unexpected token `|'"));
		i++;
	}
	if (is_chevron_type(data, i - 1))
		return (ft_error(2, "minishell: syntax error near unexpected token `newline'"));
	return (0);
}