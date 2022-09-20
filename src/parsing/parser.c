/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 15:11:10 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *get_data(void)
{
	static t_data data;

	return(&data);
}

t_data *set_data(char **env)
{
	t_data *data;

	data = get_data();
	if (!data)
		return (NULL);
	data->env = env;
	data->line = NULL;
	data->nb = 0;
	data->pipes = 0;
	data->lexer = NULL;
	return (data);
}

void	ft_parser(char *line)
{
	t_data *data;
	
	(void)line;
	(void)data;
}