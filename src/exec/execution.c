/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/13 18:05:28 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	if (data->actual == data->args && is_builtin(data))
		exec_builtout(data);
	else
	{
		signal(SIGQUIT, sigquit_handler);
		g_sigstatus.process = 1;
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
		if (data->exec[data->actual - 1].heredoc)
			signal(SIGQUIT, SIG_IGN);
		data->pid[data->actual - 1] = fork();
		if (data->pid[data->actual - 1] < 0)
			return ;
		if (data->pid[data->actual - 1] == 0)
			child_process(data, data->actual);
		if (data->pid[data->actual - 1] > 0)
		{	
			parent_process(data);
			if (data->actual <= data->args)
				exec_process(data);
		}
	}
}

void	parent_process(t_data *data)
{
	int	status;

	signal(SIGINT, sig_handler2);
	if (data->exec[data->actual - 1].heredoc)
		waitpid(data->pid[data->actual - 1], 0, WEXITSTATUS(status));
	if (data->fd[1] > 2)
		close(data->fd[1]);
	if (data->oldfd > 2)
		close(data->oldfd);
	data->oldfd = data->fd[0];
	data->actual += 1;
}

void	child_process(t_data *data, int cmd)
{
	int		builtin;
	char	**bash;

	builtin = 0;
	bash = NULL;
	signal(SIGINT, sig_handler);
	while (g_sigstatus.process)
	{
		if (handle_fd(data, cmd))
			execute(data, cmd, builtin, bash);
		else
			exit(EXIT_FAILURE);
	}
}

void	execute(t_data *data, int cmdnb, int builtin, char **bash)
{
	char	**cmd;

	cmd = getcmd(data, cmdnb);
	if (!cmd)
		exit(0);
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
