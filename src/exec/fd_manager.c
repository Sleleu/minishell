/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/30 18:52:06 by rvrignon         ###   ########.fr       */
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
	close(data->fd[0]);
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
	close(data->fd[1]);
	return (1); 
}

int		islast(t_data *data, char *infile, int cmd)
{
	t_parse *parse;
	int		return_value;
	int		i;
	
	parse = data->parse;
	i = 0;
	return_value = 0;
	while (parse[i].cmd != cmd)
		i++;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (return_value && (parse[i].type == INFILE || parse[i].type == LIMITER))
			return (0);
		if (parse[i].type == INFILE && parse[i].str == infile)
			return_value++;
		i++;
	}
	return (return_value);
}

void	heredoc_process(t_data *data, int cmd)
{
	t_parse *parse;
	int		i;
	char	*line;

	parse = data->parse;
	i = 0;
	while (parse[i].type != FINISH && parse[i].cmd != cmd)
		i++;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (parse[i].type == LIMITER)
		{
			ft_putstr_fd("> ", 2);
			line = get_next_line(0);
			while (line && (ft_strncmp(line, parse[i].str, ft_strlen(line) - 1) != 0 || line[0] == '\n'))
			{
				if (data->exec[cmd - 1].heredoc == 1)
					write(data->fd[1], line, ft_strlen(line));
				free(line);
				ft_putstr_fd("> ", 2);
				line = get_next_line(0);
			}
			data->exec[cmd - 1].heredoc--;
		}
		i++;
	}
}

int		handle_fd(t_data *data, int cmd)
{
	int heredoc;

	heredoc = 0;
	
	// HANDLE HEREDOC
	if (data->exec[cmd - 1].heredoc > 0)
	{
		heredoc = 1;
		heredoc_process(data, cmd);
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
	}
	
	// HANDLE INFILE
	if (data->exec[cmd - 1].infile && islast(data, data->exec[cmd - 1].infile, cmd))
	{
		if (!handle_infile(data, cmd))
			return (0);
	}
	else if (!heredoc)
	{
		close(data->fd[0]);
		if (cmd > 1)
			dup2(data->oldfd, STDIN_FILENO);
	}
	
	// HANDLE OUTFILE
	if (data->exec[cmd - 1].outfile)
	{		
		if (!handle_outfile(data, cmd))
			return (0);
	}
	else
		if (cmd < data->args)
			dup2(data->fd[1], STDOUT_FILENO);
		else
			close(data->fd[1]);
	return (1);
}
