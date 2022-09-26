/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 13:16:32 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, data->exec[cmd - 1].cmd);
	exit(0);
}

void	exec_process(t_data *data)
{
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid = fork();
		if (data->pid < 0)
			error();
		if (data->pid == 0)
			child_process(data, data->actual);
		if (data->pid > 0)
		{
			if (data->fd[1] > 0)
				close(data->fd[1]);
			if (data->oldfd > 0)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual++;
			if (data->actual < data->args)
				exec_process(data);
		}
		wait(0);
	}
}

int	execution(t_data *data)
{
	exec_process(data);
	return (0);
}
