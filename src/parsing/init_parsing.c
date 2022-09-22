/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:49:43 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/22 15:13:54 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	select_file(t_data **data, int i)
{
	if (token_type_chevron(data, i) == INF_CHEVRON)
		(*data)->parse[i + 1].type = INFILE;
	else if (token_type_chevron(data, i) == SUP_CHEVRON)
		(*data)->parse[i + 1].type = OUTFILE_T;
	else if (token_type_chevron(data, i) == D_SUP_CHEVRON)
		(*data)->parse[i + 1].type = OUTFILE_A;
	else if (token_type_chevron(data, i) == D_INF_CHEVRON)
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

void	init_finish_token(t_data **data, int i)
{
	(*data)->parse[i].type = FINISH;
	(*data)->parse[i].str = NULL;
	if (ft_lexerlen((*data)->lexer))
		(*data)->parse[i].cmd = (*data)->parse[i - 1].cmd;
	else
		(*data)->parse[i].cmd = 1;
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
		(*data)->parse[i].cmd = ptr->cmd;
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
	init_finish_token(data, i);
}
