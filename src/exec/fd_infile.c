/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:07:39 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 02:10:10 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_infile(t_data *data, int cmd, int i)
{
	int	fd;

	if (ft_ambigous(data, cmd, 'i', i))
		exit(0);
	fd = open(data->exec[cmd - 1].infile[i].file, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(data->exec[cmd - 1].infile[i].file);
		close_pipes(data);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(data->fd[0]);
	return (1);
}

static int	utils_in(t_data *data, int cmd, int i)
{
	int	fd;

	if (islastfile(data->exec[cmd - 1].infile, i))
	{
		if (data->exec[cmd - 1].heredoc > 0)
		{
			if (!fd_heredoc(data, cmd, 0))
				return (0);
		}
		if (!handle_infile(data, cmd, i))
			return (0);
	}
	else
	{
		if (ft_ambigous(data, cmd, 'i', i))
			exit(0);
		fd = open(data->exec[cmd - 1].infile[i].file, O_RDONLY, 0644);
		if (fd < 0)
		{
			perror(data->exec[cmd - 1].infile[i].file);
			exit(1);
		}
		close(fd);
	}
	return (1);
}

int	fd_infile(t_data *data, int cmd)
{
	int	i;
	int	heredoc;

	heredoc = data->exec[cmd - 1].heredoc;
	i = -1;
	if (data->exec[cmd - 1].infile)
	{
		while (data->exec[cmd - 1].infile[++i].token != FINISH)
		{
			if (!utils_in(data, cmd, i))
				return (0);
		}
	}
	if (!islastfile(data->exec[cmd - 1].infile, i - 1) && heredoc)
	{
		if (!fd_heredoc(data, cmd, 1))
			return (0);
	}
	else if (!heredoc)
	{
		close(data->fd[0]);
		if (cmd > 1)
			dup2(data->oldfd, STDIN_FILENO);
	}
	return (1);
}
