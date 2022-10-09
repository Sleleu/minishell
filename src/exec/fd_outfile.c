/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:43:54 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 22:55:32 by rvrignon         ###   ########.fr       */
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
	int		fileout;
	char	*file;

	file = data->exec[cmd - 1].outfile[i];
	fileout = -1;
	if (ft_ambigous(data, cmd, 'o', i))
		exit(0);
	if (get_outfile_type(data, cmd, i) == OUTFILE_T)
		fileout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
		fileout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fileout < 0)
	{
		perror(file);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(fileout, STDOUT_FILENO);
	close(data->fd[1]);
	return (1);
}

static int	utils_out(t_data *data, int cmd, int i)
{
	char	*file;
	int		test;

	file = data->exec[cmd - 1].outfile[i];
	if (islastoutfile(data->exec[cmd - 1].outfile, i))
	{
		if (!handle_outfile(data, cmd, i))
			return (0);
	}
	else
	{
		if (ft_ambigous(data, cmd, 'o', i))
			exit(0);
		if (get_outfile_type(data, cmd, i) == OUTFILE_T)
			test = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
			test = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (test < 0)
		{
			perror(data->exec[cmd - 1].outfile[i]);
			return (0);
		}
		close(test);
	}
	return (1);
}

int	fd_outfile(t_data *data, int cmd)
{
	int		i;

	i = -1;
	if (data->exec[cmd - 1].outfile)
	{
		while (data->exec[cmd - 1].outfile[++i])
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
