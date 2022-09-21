/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/21 14:42:19 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_type_token(t_data **data)
{
	int i;

	i = 0;
	(void)i;
	if ((*data)->parse[0].type == PIPE)
		return (ft_error(2, "minishell: syntax error near unexpected token `|'"));
	return (0);
}

void	init_parsing(t_data **data)
{
	t_lexer	*ptr;
	int 	i;
	
	ptr = (*data)->lexer;
	i = 0;
	(*data)->parse = memcenter(MALLOC, sizeof(t_parse)
		* (ft_lexerlen((*data)->lexer) + 1), NULL, PARSING);
	while (ptr)
	{
		(*data)->parse[i].type = ptr->type;
		if ((*data)->parse[i].type == WORD)
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
	int error;
	
	error = 0;
	init_parsing(data);
	if ((error = error_type_token(data)) != 0)
		return (error);
	//FREE LEXER ICI;
	return (0);
}
