/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/03 20:55:05 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_data *data, int cmd)
{
	if (handle_fd(data, cmd))
		execute(data, cmd);
}

int		heredoc(t_data *data, int cmd)
{
	t_parse *parse;

	parse = data->parse;
	(void)parse;
	(void)cmd;
	return (0);
	
}

int	exec_process(t_data *data)
{
	if (data->actual <= data->args)
	{
		if (pipe(data->fd) == -1)
			return (0);
		data->pid = fork();
		if (data->pid < 0)
			return (0);
		if (data->pid == 0)
			child_process(data, data->actual);
		if (data->pid > 0 && data->actual <= data->args)
		{
			if (heredoc(data, data->actual))
				wait(0);
			if (data->fd[1] > 2)
				close(data->fd[1]);
			if (data->oldfd > 2)
				close(data->oldfd);
			data->oldfd = data->fd[0];
			data->actual += 1;
			exec_process(data);
		}
		wait(0);
	}

	return (1);
}

int is_builtin(t_data *data){
	char	**cmd;
	
	cmd = getcmd(data, 1);
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		return (ft_cd(cmd[1], data->env));
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		return (ft_export(&data, cmd));
	else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		return (ft_exit(cmd));
	return (42);
}

int	execution(t_data *data)
{
	int	code;
	// print_both(data);
	code = is_builtin(data);
	if (data->actual == data->args && code != 42)
		return (code);
	else
	{
		code = exec_process(data);
		close_pipes(data);
		return (code);
	}
	return (1);
}
