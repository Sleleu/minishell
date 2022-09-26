/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 15:05:12 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, data->exec[cmd - 1].cmd);
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
		if (data->pid > 0 && data->actual < data->args)
		{
			if (data->fd[1] > 0)
				close(data->fd[1]);
			if (data->oldfd > 0)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual++;
			exec_process(data);
		}
		// waitpid(data->pid, 0, WCONTINUED);
		wait(0);
	}
}

int	execution(t_data *data)
{
	exec_process(data);
	return (0);
}
