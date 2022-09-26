/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 18:08:35 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type get_outfile_type(t_data *data, int cmd)
{
	t_parse *parse;
	int		i;

	parse = data->parse;
	i = -1;
	while (parse[++i].type != FINISH)
	{
		if (parse[i].cmd == cmd && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			return (parse[i].type);
	}
	return (FINISH);
}

int		handle_infile(t_data *data, int cmd)
{
	int filein; 
	
	filein = open(data->exec[cmd - 1].infile, O_RDONLY, 0644);
	if (filein < 0)
	{
		perror(data->exec[cmd - 1].infile);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	dup2(data->fd[0], filein);
	return (1);
}

int		handle_outfile(t_data *data, int cmd)
{
	int fileout;
	
	if (get_outfile_type(data, cmd) == OUTFILE_T)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd) == OUTFILE_A)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fileout < 0)
	{
		perror(data->exec[cmd - 1].outfile);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(fileout, STDOUT_FILENO);
	dup2(data->fd[1], fileout);
	return (1); 
}

int		handle_fd(t_data *data, int cmd)
{
	// HANDLE INFILE
	if (data->exec[cmd - 1].infile)
	{
		if (!handle_infile(data, cmd))
			return (0);
	}
	else
	{
		if (cmd == 1)	
			dup2(STDIN_FILENO, data->fd[0]);
		else
			dup2(data->oldfd, STDIN_FILENO);
	}
	
	// HANDLE OUTFILE
	if (data->exec[cmd - 1].outfile)
	{		
		if (!handle_outfile(data, cmd))
			return (0);
	}
	else
	{
		if (cmd < data->args)
			dup2(data->fd[1], STDOUT_FILENO);
	}
	return (1);
}
