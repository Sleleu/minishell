/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 18:09:23 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error(int error, char *str)
{
	dprintf(2, "%s\n", str);
	return (error);
}

int	ft_parser(t_data **data)
{	
	t_lexer *lexer;

	lexer = (*data)->lexer;
	if (lexer->type == PIPE)
	 	return (ft_error(1, "minishell: syntax error near unexpected token `|'"));
	while (lexer)
	{
		//if (lexer->type == WORD)
		
		lexer = lexer->next;
	}

/* [PRINT TEST] */

	t_lexer *ptr;

	ptr = (*data)->lexer;
	while (ptr)
	{
		printf("TYPE : %d | CONTENU : %s\n", ptr->type, ptr->content);
	 	ptr = ptr->next;
	}
	return (0);
}

// lexer->type == WORD;

/*	(void)data;
	lexer = get_data()->lexer;
	if (lexer->type == PIPE)
	 	return (ft_error(1, "minishell: syntax error near unexpected token `|'"));
	while (lexer)
	{
		if (lexer->type == WORD)
			execve(cmd[0], cmd, NULL);
		lexer = lexer->next;
	}
	return (0); */