/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 21:43:27 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	if (data->actual == data->args && is_builtin(data))
		exec_builtout(data);
	else
	{
		exec_process(data);
		data->exit[0] = 0;
		data->exit[1] = getcode(data);
		close_pipes(data);
		unlink(data->tmp);
	}
}

void	exec_process(t_data *data)
{
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return ;
		data->pid[data->actual - 1] = fork();
		if (data->pid[data->actual - 1] < 0)
			return ;
		if (data->pid[data->actual - 1] == 0)
			child_process(data, data->actual);
		if (data->pid[data->actual - 1] > 0)
		{	
			if (data->exec[data->actual - 1].heredoc)
				wait(0);
			if (data->fd[1] > 2)
				close(data->fd[1]);
			if (data->oldfd > 2)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual += 1;
			if (data->actual <= data->args)
				exec_process(data);
		}
	}
}

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, cmd);
	else
		exit(EXIT_FAILURE);
}

int	handle_fd(t_data *data, int cmd)
{
	if (!fd_infile(data, cmd))
		return (0);
	if (!fd_outfile(data, cmd))
		return (0);
	return (1);
}

void	execute(t_data *data, int cmdnb)
{
	char	**cmd;
	char	**bash;
	int		builtin;

	cmd = getcmd(data, cmdnb);
	if (!cmd)
		exit (0);
	if (cmd[0][0] == '\0')
		return (err_return(cmd));
	builtin = trybuiltin(data, cmd);
	if (builtin >= 0)
		exit(builtin);
	if (ft_strlen(cmd[0]) > 0 && !is_path(cmd[0]))
		cmd[0] = setpath(cmd[0], data->env);
	if (!cmd[0] || access(cmd[0], X_OK != 0))
		return (err_return(cmd));
	if (execve(cmd[0], cmd, data->env) == -1)
	{
		if (access(cmd[0], X_OK != 0))
			perror(cmd[0]);
		else
		{
			bash = test(cmd);
			if (execve(bash[0], bash, data->env) == -1)
				exit(EXIT_FAILURE);
		}
	}
}
