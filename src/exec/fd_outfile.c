/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:43:54 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 19:27:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type	get_outfile_type(t_data *data, int cmd, int j)
{
	t_parse	*parse;
	int		i;

	parse = data->parse;
	i = gotoparsecmd(data, cmd);
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (!j && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			return (parse[i].type);
		else if (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T)
			j--;
		i++;
	}
	return (FINISH);
}

int	handle_outfile(t_data *data, int cmd, int i)
{
	int		fd;
	char	*file;

	file = data->exec[cmd - 1].outfile[i].file;
	fd = -1;
	if (ft_ambigous(data, cmd, 'o', i))
		exit(1);
	if (get_outfile_type(data, cmd, i) == OUTFILE_T)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		close_pipes(data);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(data->fd[1]);
	return (1);
}

static int	utils_out(t_data *data, int cmd, int i)
{
	char	*file;
	int		fd;

	file = data->exec[cmd - 1].outfile[i].file;
	if (islastfile(data->exec[cmd - 1].outfile, i))
	{
		if (!handle_outfile(data, cmd, i))
			return (0);
	}
	else
	{
		if (ft_ambigous(data, cmd, 'o', i))
			exit(1);
		if (get_outfile_type(data, cmd, i) == OUTFILE_T)
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(data->exec[cmd - 1].outfile[i].file);
			exit (1);
		}
		close(fd);
	}
	return (1);
}

int	fd_outfile(t_data *data, int cmd)
{
	int		i;

	i = -1;
	if (data->exec[cmd - 1].outfile)
	{
		while (data->exec[cmd - 1].outfile[++i].token != FINISH)
		{
			if (!utils_out(data, cmd, i))
				return (0);
		}
	}
	else
	{
		if (cmd < data->args)
			dup2(data->fd[1], STDOUT_FILENO);
		else
			close(data->fd[1]);
	}
	return (1);
}
