/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:58:35 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/13 17:16:31 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	getcode(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	i = -1;
	while (++i < data->args)
	{
		pid = waitpid(data->pid[i], &status, WUNTRACED);
		if (pid == data->pid[data->args - 1])
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else
				status = 128 + WTERMSIG(status);
		}
	}
	return (status);
}

int	ft_ultracmp(char *first, char *second)
{
	if (!ft_strncmp(first, second, ft_strlen(first))
		&& ft_strlen(first) == ft_strlen(second))
		return (0);
	return (1);
}

t_files	exec_file_process(char *parse)
{
	t_files	files;

	if (!parse)
		files.file = NULL;
	else
		files.file = parse;
	files.token = INFILE;
	return (files);
}

int	handle_fd(t_data *data, int cmd)
{
	if (!fd_infile(data, cmd))
		return (0);
	if (!fd_outfile(data, cmd))
		return (0);
	return (1);
}
