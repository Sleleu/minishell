/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/16 00:34:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *set_data(char **env)
{
	t_data *data;

	data = get_data();
	if (!data)
		return (NULL);
	data->env = env;
	data->line = NULL;
	data->nb = 0;
	data->pipes = NULL;
	return (data);
}

t_data *update_data(char *line)
{
	t_data	*data;
	
	data = get_data();
	if (!data)
		return (NULL);
	data->line = line;
	data->nb++;
	if (pipe_exist(line))
		data->pipes = create_pipes(line);
	return (data);
}

void	ft_parser(char *line)
{
	t_data *data;

	data = update_data(line);
	(void)data;
}