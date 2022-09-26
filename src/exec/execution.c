/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 21:29:21 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
	{
		//dprintf(2, "CMD %d || FD[0] = %d && FD[1] = %d && oldfd = %d\n", cmd, data->fd[0], data->fd[1], data->oldfd);
		execute(data, cmd);
	}
}

void	exec_process(t_data *data)
{
	// int nb;
	
	// nb = data->actual;
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
			child_process(data, data->actual);
		if (data->pid > 0 && data->actual < data->args)
		{
			// Handle Heredoc; 
			if (data->fd[1] > 2)
				close(data->fd[1]);
			if (data->oldfd > 2)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual++;
			exec_process(data);
		}
		// dprintf(2, "%d : Finish ??\n", nb);
		wait(NULL);
		// dprintf(2, "%d : Finished\n", nb);
	}
}

int	execution(t_data *data)
{
	exec_process(data);
	close_pipes(data);
	return (1);
}
