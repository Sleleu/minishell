/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:29:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/22 20:09:00 by rvrignon         ###   ########.fr       */
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
	data->args = 1;
	data->env = env;
	data->line = NULL;
	data->exec = NULL;
	data->lexer = NULL;
	data->parse = NULL;
	data->memcenter = NULL;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->oldfd = -1;
	return (data);
}