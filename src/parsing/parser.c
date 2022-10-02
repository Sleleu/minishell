/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/02 17:50:26 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parser(t_data **data)
{
	int	error;

	init_parsing(data);
	error = error_type_token(data);
	if (error != 0)
		return (-1);
	assign_file(data);
	int i = 0;
	while (token_type(data, i) != FINISH)
	{
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);
		i++;
	}
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);
	if (!parse_quotes(data))
		return (-1);
	convert_env(data);
	return (0);
}
// FREE LE LEXER
//TEST
/*	int i = 0;
	while (token_type(data, i) != FINISH)
	{
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);
		i++;
	}
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);*/