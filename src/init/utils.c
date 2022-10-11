/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:29:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 02:29:15 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_data	*set_data(char **env)
{
	t_data	*data;

	data = get_data();
	if (!data)
		return (NULL);
	data->env = env;
	data->memcenter = NULL;
	data->actual = 1;
	data->args = 1;
	data->line = NULL;
	data->exec = NULL;
	data->lexer = NULL;
	data->parse = NULL;
	data->pid = NULL;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->oldfd = -1;
	data->heredoc = 0;
	data->tmp = "/tmp/minishell_tmp.txt";
	data->tmpfd = 0;
	data->exit[0] = 0;
	data->exit[1] = 0;
	return (data);
}

void	restore_data(void)
{
	t_data	*data;

	data = get_data();
	if (!data)
		return ;
	data->actual = 1;
	data->args = 1;
	data->line = NULL;
	data->exec = NULL;
	data->lexer = NULL;
	data->parse = NULL;
	data->pid = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->oldfd = -1;
	data->heredoc = 0;
}
