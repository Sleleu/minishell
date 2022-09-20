/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:29:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 18:14:07 by rvrignon         ###   ########.fr       */
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
	data->pipex = NULL;
	data->lexer = NULL;
	data->parsing = NULL;
	data->memcenter = NULL;
	return (data);
}
