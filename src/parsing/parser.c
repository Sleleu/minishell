/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 21:41:41 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error(int error, char *str)
{
	dprintf(2, "%s\n", str);
	return (error);
}

int	ft_lexerlen(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
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

void	ft_parser(t_data **data)
{	
	init_parsing(data);
	//FREE LEXER ICI;
}
