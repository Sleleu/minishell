/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:13:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/22 19:57:37 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		handle_fdt(t_data *data)
{
	if (data->exec[0].infile)
	{
		data->fd[0] = open(data->exec[0].infile, O_RDONLY, 0644);
		if (data->fd[0] < 0)
		{
			perror(data->exec[0].infile);
			return (0);
		}
		dup2(data->fd[0], STDIN_FILENO); 
	}
	else
		data->fd[0] = 0;
	if (data->exec[0].outfile)
	{
		data->fd[1] = open(data->exec[0].outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->fd[1] < 0)
		{
			perror(data->exec[0].outfile);
			return (0);
		}
		dup2(data->fd[1], STDOUT_FILENO);  
	}
	else
		data->fd[1] = 1;
	return (1);
}

static void	child_process(t_data *data)
{
	// exit(EXIT_FAILURE);
	if (handle_fdt(data))
		execute(data, data->exec[0].cmd);
}

void	exec_simple_process(t_data *data)
{
	t_exec	*exec;
	
	exec = data->exec;
	exec[0].pid = fork();
	if (exec[0].pid < 0)
		return ;
	if (exec[0].pid == 0)
		child_process(data);
	if (exec[0].pid > 0)
		wait(0);
}

int	exec_simple(t_data *data)
{
	// print_both(data);
	exec_simple_process(data);
	return (0);
}