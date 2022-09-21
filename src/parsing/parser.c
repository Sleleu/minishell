/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/21 19:00:57 by sleleu           ###   ########.fr       */
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
		return (ft_error(2, "minishell: syntax error near unexpected token `newline'"));
	if (token_type(data, i) == INF_CHEVRON)
		return (ft_error(2, "minishell: syntax error near unexpected token `<'"));
	else if (token_type(data, i) == SUP_CHEVRON)
		return (ft_error(2, "minishell: syntax error near unexpected token `>'"));
	else if (token_type(data, i) == D_INF_CHEVRON)
		return (ft_error(2, "minishell: syntax error near unexpected token `<<'"));
	else if (token_type(data, i) == D_SUP_CHEVRON)
		return (ft_error(2, "minishell: syntax error near unexpected token `>>'"));
	else
		return (0);
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

void	select_file(t_data **data, int i)
{
	if (token_type(data, i) == INF_CHEVRON)
		(*data)->parse[i + 1].type = INFILE;
	else if (token_type(data, i) == SUP_CHEVRON)
		(*data)->parse[i + 1].type = OUTFILE_T;
	else if (token_type(data, i) == D_SUP_CHEVRON)
		(*data)->parse[i + 1].type = OUTFILE_A;
	else if (token_type(data, i) == D_INF_CHEVRON)
		(*data)->parse[i + 1].type = LIMITER;
}

void	assign_file(t_data **data)
{
	int	i;

	i = 0;
	while (token_type(data, i) != FINISH)
	{
		if (is_chevron_type(data, i))
			select_file(data, i);
		i++;
	}
}

void	init_parsing(t_data **data)
{
	t_lexer	*ptr;
	int		i;

	ptr = (*data)->lexer;
	i = 0;
	(*data)->parse = memcenter(MALLOC, sizeof(t_parse)
			* (ft_lexerlen((*data)->lexer) + 1), NULL, PARSING);
	while (ptr)
	{
		(*data)->parse[i].type = ptr->type;
		if (token_type(data, i) == WORD)
		{
			(*data)->parse[i].str = memcenter(MALLOC, sizeof(char)
					* ft_strlen(ptr->content) + 1, NULL, PARSING);
			ft_strcpy((*data)->parse[i].str, ptr->content);
		}
		else
			(*data)->parse[i].str = NULL;
		i++;
		ptr = ptr->next;
	}
	(*data)->parse[i].type = FINISH;
	(*data)->parse[i].str = NULL;
}

int	ft_parser(t_data **data)
{
	int	error;

	init_parsing(data);
	error = error_type_token(data);
	if (error != 0)
		return (error);
	assign_file(data);
/*	
	SI TU VEUX TESTER UN TRUC ROLLEX
	int i = 0;
	while (token_type(data, i) != FINISH)
	{
		printf("CONTENT %s | TYPE %d\n", (*data)->parse[i].str, (*data)->parse[i].type);
		i++;
	}
		printf("CONTENT %s | TYPE %d\n", (*data)->parse[i].str, (*data)->parse[i].type);
		*/
	return (0);
}

// FREE LE LEXER
